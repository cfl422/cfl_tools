#include <bits/stdc++.h>
#include <windows.h>
//#define OUTPUT_PROCESS_CREATER_LOGS
#include "ProcessCreater.h"
#include "shellworker.h"
using namespace std;
//using namespace Cfl;
HWND mainWindow;
int main (int argc, char** argv) {


	if (argc == 1) {
		mainWindow = GetConsoleWindow();
		SetWindowText (mainWindow, "csh");
		return Cfl::onlineshellmain();
	}
	else
		return Cfl::shellserver (argc, argv);

	return 0;
}
