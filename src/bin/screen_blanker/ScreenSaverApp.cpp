/*
 * Copyright 2003, Michael Phipps. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#include <stdio.h>
#include <Screen.h>
#include <image.h>
#include <StorageDefs.h>
#include <FindDirectory.h>
#include <SupportDefs.h>
#include <File.h>
#include <Path.h>
#include <string.h>
#include <Beep.h>

#include "ScreenSaverApp.h"


// Start the server application. Set pulse to fire once per second.
// Run until the application quits.
int main(int, char**) 
{	
	ScreenSaverApp myApplication;
	myApplication.Run();
	return(0);
}

// Construct the server app. Doesn't do much, at this point.
ScreenSaverApp::ScreenSaverApp()
	: BApplication(SCREEN_BLANKER_SIG),
	fWin(NULL) 
{
	fBlankTime = system_time();
}


void 
ScreenSaverApp::ReadyToRun(void) 
{
	if (!fPref.LoadSettings()) 
		exit(1);
	else {	// If everything works OK, create a BDirectWindow and start the render thread.
		BScreen theScreen(B_MAIN_SCREEN_ID);
		fWin = new SSAwindow(theScreen.Frame());
		fPww = new PasswordWindow();
		fThrd = new ScreenSaverThread(fWin,fWin->fView,&fPref);

		fSaver = fThrd->LoadAddOn();
		if (!fSaver)
			exit(1);
		fWin->SetSaver(fSaver);
		fWin->SetFullScreen(true);
		fWin->Show();
		fThreadID = spawn_thread(ScreenSaverThread::ThreadFunc,"ScreenSaverRenderer",0,fThrd);
		resume_thread(fThreadID);
		HideCursor();
	}
}


void 
ScreenSaverApp::ShowPW(void) 
{
	fWin->Lock();
	suspend_thread(fThreadID);
	if (B_OK==fWin->SetFullScreen(false)) {
		fWin->Sync();
		ShowCursor();
		fPww->Show();
		fPww->Sync();
	}
	fWin->Unlock();
}


void 
ScreenSaverApp::MessageReceived(BMessage *message) 
{
	switch(message->what) {
		case UNLOCK_MESSAGE:
			if (strcmp(fPww->GetPassword(),fPref.Password())) {
				beep();
				fPww->Hide();
				fWin->SetFullScreen(true);
				if (fThreadID)
					resume_thread(fThreadID);
				}
				else  {
					printf ("Quitting!\n");
					Shutdown();
				}
			break;
    		case 'MOO1':
			if (real_time_clock()-fBlankTime>fPref.PasswordTime())
				ShowPW();
			else 
			Shutdown();
			break;
		default:
			BApplication::MessageReceived(message);
 			break;
	}
}


void 
ScreenSaverApp::Shutdown(void) 
{
	if (fWin)
		fWin->Hide();
	if (fThreadID)
		kill_thread(fThreadID);
	if (fThrd)
		delete fThrd;
	Quit();
}
