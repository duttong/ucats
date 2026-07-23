import itertools
import logging
from collections import defaultdict
from dataclasses import dataclass, field
from threading import Event, Lock, Thread
from time import monotonic
from typing import Callable, Optional, Tuple


@dataclass
class ScheduledTask:
    delay: float
    interval: Optional[float]
    function: Callable
    args: Tuple = field(default_factory=tuple)
    priority: int = 50
    resource: Optional[str] = None
    skip_if_running: bool = False
    skip_if_resource_busy: bool = False
    name: Optional[str] = None
    next_run: float = 0.0
    running: int = 0
    enabled: bool = True
    sequence: int = 0

    def __post_init__(self):
        if self.name is None:
            self.name = self.function.__name__


class Scheduler:
    """Single scheduler thread that dispatches all timed UCATS work.

    Tasks remain synchronous; the scheduler only coordinates when they are
    launched and applies skip rules for best-effort polling work.
    """

    def __init__(self, tick=0.01):
        self.tick = tick
        self.tasks = []
        self._thread = None
        self._stop_event = Event()
        self._lock = Lock()
        self._sequence = itertools.count()
        self._resource_counts = defaultdict(int)

    def add_task(self, delay, interval, function, args=None, priority=50,
                 resource=None, skip_if_running=False,
                 skip_if_resource_busy=False, name=None):
        if args is None:
            args = ()

        task = ScheduledTask(
            delay=max(0.0, delay),
            interval=interval,
            function=function,
            args=tuple(args),
            priority=priority,
            resource=resource,
            skip_if_running=skip_if_running,
            skip_if_resource_busy=skip_if_resource_busy,
            name=name,
            next_run=monotonic() + max(0.0, delay),
            sequence=next(self._sequence),
        )
        with self._lock:
            self.tasks.append(task)

        logging.debug(
            'Scheduled task %s delay=%s interval=%s priority=%s resource=%s '
            'skip_if_running=%s skip_if_resource_busy=%s',
            task.name, delay, interval, priority, resource,
            skip_if_running, skip_if_resource_busy,
        )
        return task

    def start(self):
        if self._thread is not None and self._thread.is_alive():
            return

        self._stop_event.clear()
        self._thread = Thread(target=self._run, daemon=True, name='ucats-scheduler')
        self._thread.start()
        logging.info('Scheduler started tick=%s tasks=%s', self.tick, len(self.tasks))

    def stop(self):
        self._stop_event.set()
        if self._thread is not None and self._thread.is_alive():
            self._thread.join(timeout=1.0)
        logging.info('Scheduler stopped')
        with self._lock:
            self.tasks = []
            self._resource_counts.clear()

    def _run(self):
        while not self._stop_event.is_set():
            now = monotonic()
            with self._lock:
                due = [t for t in self.tasks if t.enabled and t.next_run <= now]
                next_due = min(
                    (t.next_run for t in self.tasks if t.enabled),
                    default=None,
                )

            if due:
                for task in sorted(due, key=lambda t: (t.next_run, t.priority, t.sequence)):
                    self._dispatch(task, now)
                continue

            if next_due is None:
                self._stop_event.wait(self.tick)
                continue

            self._stop_event.wait(min(max(0.0, next_due - now), self.tick))

    def _dispatch(self, task, now):
        with self._lock:
            if not task.enabled:
                return

            resource_busy = (
                task.resource is not None and self._resource_counts[task.resource] > 0
            )
            if task.skip_if_running and task.running > 0:
                self._reschedule(task, now)
                logging.debug('Skipping task %s: previous invocation still running', task.name)
                return

            if task.skip_if_resource_busy and resource_busy:
                self._reschedule(task, now)
                logging.debug('Skipping task %s: resource %s busy', task.name, task.resource)
                return

            task.running += 1
            if task.resource is not None:
                self._resource_counts[task.resource] += 1
            if task.interval is None:
                task.enabled = False
            else:
                self._reschedule(task, now)

        logging.debug(
            'Dispatching task %s priority=%s resource=%s args=%s',
            task.name, task.priority, task.resource, task.args
        )
        Thread(target=self._execute, args=(task,), daemon=True).start()

    def _reschedule(self, task, now):
        if task.interval is None:
            task.enabled = False
            return

        while task.next_run <= now:
            task.next_run += task.interval

    def _execute(self, task):
        try:
            task.function(*task.args)
        except Exception:
            logging.exception('Scheduled task %s failed', task.name)
        finally:
            with self._lock:
                task.running = max(0, task.running - 1)
                if task.resource is not None:
                    self._resource_counts[task.resource] = max(
                        0, self._resource_counts[task.resource] - 1
                    )
