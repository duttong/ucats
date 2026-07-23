#!/usr/bin/arch -i386 /usr/bin/python2.6

import wx

UDP_PORT = 4600

class MainWindow(wx.Frame):
	def __init__(self, parent, title):
		wx.Frame.__init__(self, parent, title=title, size=(300,200))
		self.control = wx.TextCtrl(self, style=wx.TE_MULTILINE)
		self.CreateStatusBar()    # A Statusbar in the bottom of the window
		
		# Setting up the menu.
		filemenu = wx.Menu()
		
		# wx.ID_ABOUT and wx.ID_EXIT are standard IDs provided by wxWidgets.
		item = filemenu.Append(wx.ID_ABOUT, "&About Kudisplay", "Program to save and display UCATS Ku-band data")
		self.Bind(wx.EVT_MENU, self.OnAbout, item)
		item = filemenu.Append(wx.ID_EXIT,"&Exit"," Terminate the program")
		self.Bind(wx.EVT_MENU, self.OnQuit, item)
		item = filemenu.Append(wx.ID_PREFERENCES, "&Preferences")
		self.Bind(wx.EVT_MENU, self.OnPrefs, item)
		
		# Creating the menubar.
		menuBar = wx.MenuBar()
		menuBar.Append(filemenu,"&Config") # Adding the "filemenu" to the MenuBar
		self.SetMenuBar(menuBar)  # Adding the MenuBar to the Frame content.
		
		self.quote = wx.StaticText(self, label="Your quote :", pos=(20, 30), size=(200, -1))
		self.Show(True)

	def OnAbout(self, Event):
		# A message dialog box with an OK button. wx.OK is a standard ID in wxWidgets.
		dlg = wx.MessageDialog(self, "Geoff Dutton, Ver 1.0", "Program to save and display UCATS Ku-band retrieved data", wx.OK)
		dlg.ShowModal() # Show it
		dlg.Destroy() # finally destroy it when finished.
		
	def OnPrefs(self, Event):
		menu = wx.Menu()
		item = menu.Append(UDP_PORT, "&Default Port: "+str(UDP_PORT))
		self.Show(True)
		'''
		dlg = wx.MessageDialog(self, "This would be an preferences Dialog\n"
									 "If there were any preferences to set.\n",
								"Preferences", wx.OK | wx.ICON_INFORMATION)
		dlg.ShowModal()
		dlg.Destroy()
		'''
		
		
	def OnQuit(self, Event):
		self.Destroy()
		
	

app = wx.App(False)
frame = MainWindow(None, "UCATS")
app.MainLoop()
