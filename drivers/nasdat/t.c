#include <time.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	struct tm *local, *gm;
	time_t t;
	char *txt = "abc,def,ghi";
	char work[80];
	char *first;

	t = time(NULL);
	local = localtime(&t);
	printf("local time and date: %s\n", asctime(local));
	gm = gmtime(&t);
	printf("gmt time and date: %s\n", asctime(gm));

	strcpy(work, txt);
	first = strtok(work, ",");
	printf("%s %s %s\n", txt, first, strstr(txt, ","));
	
	return 0;
}