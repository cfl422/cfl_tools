#ifndef SHELLWORKER_H
#define SHELLWORKER_H
#include "config.h"
#include "head.h"
#include "ApplicationOperations.h"
#include "ShellBasicServices.h"
#include "ProcessCreater.h"
using namespace std;
namespace Cfl {
	const int maxcmdargs = 8192;
	struct CmdApp {
		string app;
		int cmdcnt;
		string command[maxcmdargs];
		CmdApp();
		CmdApp (string zapp);
		CmdApp (string zapp, int zcmdcnt, string* zcommand);
		~CmdApp();
	};

	CmdApp GetCmdAppinString (string cmd) ;
	CmdApp GetNowCmdLine (istream& ost);
	int shellSonProcessRunTime (string app, int cmdcnt, string command[], string filename ) ;
	CmdApp GetNowCmdLine (ostream& ost);
	int shellworker (ostream& ost, string app, int cmdcnt, string* command, string filename );
	int onlineshellmain();
	int shellserver (int cmdcnt, char** cmdline);
	int shellworker (ostream& ost, CmdApp cmdapp, string filename);
};

#endif
