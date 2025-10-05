#include "shellworker.h"
namespace Cfl {

	CmdApp::CmdApp() {
		app = "";
		cmdcnt = 0;
	}

	CmdApp::CmdApp (string zapp) {
		app = zapp;
		cmdcnt = 0;
	}

	CmdApp::CmdApp (string zapp, int zcmdcnt, string* zcommand) {
		app = zapp;
		cmdcnt = zcmdcnt;

		for (int i = 0; i < cmdcnt; i++) command[i] = zcommand[i];
	}

	CmdApp::~CmdApp() {
//		delete command;
	}

	CmdApp GetCmdAppinString (string cmd) {
		CmdApp ret;
		char ch = 0;
		string now = "";

		for (int i = 0; i < sz (cmd); i++) {
//			cerr << ch << endl;
			ch = cmd[i];

			if (ch == '\n') break;
			else if (ch == ' ') {
				if (now == "") continue;

				if (ret.app == "")
					ret.app = now;
				else
					ret.command[ret.cmdcnt++] = now;

				now = "";
			}
			else if (ch > 32 && ch < 127) {
//				if (ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';

				now += ch;
			}
		}

		if (now != "") {
			if (ret.app == "") ret.app = now;
			else
				ret.command[ret.cmdcnt++] = now;
		}

#ifdef debugging
		cout << "cmdline: " << ret.app << " ";

		for (int i = 0; i < ret.cmdcnt; i++) cout << ret.command[i] << ",";

		cout << endl;
#endif
		return ret;
	}

	CmdApp GetNowCmdLine (istream& ost) {
		string cmd = "";
		getline (ost, cmd);
		return GetCmdAppinString (cmd);
	}

	int shellSonProcessRunTime ( string app, int cmdcnt, string command[], string filename) {
		string pt = "";

		for (int i = 0; i < cmdcnt; i++) pt = pt + " " + command[i];

		pt = app + pt;
		char c[sz (pt) +2];

//		if (filename != "" )pt =  (pt + " nul > " + filename);

		strep (api, pt) c[api] = pt[api];



//				cerr << "Create Process : " << app << "\n";
		return CCreateProcessIdle (c);
//				delete c;
	}

	int shellworker (ostream& ost, string app, int cmdcnt, string command[], string filename ) {
#ifdef debugging
		cout << "App:" << app << "\n";
		cout << "Command:" << " ";

		for (int i = 0; i < cmdcnt; i++) cout << command[i] << ",";

		cout << endl;
#endif
//		cout << app << endl;

		strep (i, app) if (app[i] >= 'A' && app[i] <= 'Z') app[i] += 'a' - 'A';

		if (app == "pause") Shell_BasicServices:: pause();
		else if (app == "dir" || app == "ls") Shell_BasicServices:: dir (ost);
		else if (app == "pwd") {
			string ret = Shell_BasicServices:: pwd();
			ost << ret << endl;
		}
		else if (app == "exit") Shell_BasicServices::exit();
		else if (app == "cd") {
			if (cmdcnt < 1) {
				cerr << "Too few args!\n";
				return -1;
			}

			string pt = command[0];

			for (int i = 1; i < cmdcnt; i++) pt = pt + " " + command[i];

			Shell_BasicServices::cd (pt);
		}
		else if (app == "echo") {
			if (cmdcnt < 1) {
				cerr << "Too few args!\n";
				return -1;
			}

			string pt = command[0];

			for (int i = 1; i < cmdcnt; i++) pt = pt + " " + command[i];

			Shell_BasicServices::echo (ost, pt);
		}
		else {
			string lx = getAppType (app);

			if (app != "") {
				if (lx == "exe")
					return shellSonProcessRunTime ( app, cmdcnt, command, filename);
				else if (lx == "") {
					app = app + ".exe";
					return shellSonProcessRunTime ( app, cmdcnt, command, filename);
				}
			}
		}

		return 0;
	}

	int shellworker (ostream& ost, CmdApp cmdapp, string filename ) {
		return shellworker (ost, cmdapp.app, cmdapp.cmdcnt, cmdapp.command, filename);
	}

	int onlineshellmain() {
		printf ("Cfl shell process. \n");

		while (true) {
			cout << endl;
			cout << Shell_BasicServices::pwd();
			cout << ">";
			CmdApp now = GetNowCmdLine (cin);
			shellworker (cout, now.app, now.cmdcnt, now.command, "");
		}

		return 0;
	}

	int shellserver (int cmdcnt, char** cmdline) {
		bool useFileout = false;
		ofstream nowOutputFile;
		string filename;

		for (int i = 1; i < cmdcnt; i++) {
			if (cmdline[i][0] == '-') {
				string app (cmdline[i]);

				strep (j, app) if (app[j] >= 'A' && app[j] <= 'Z') app[j] += 'a' - 'A';

				if (app == "-fo" || app == "-fileout") {
					i++;

					if (i >= cmdcnt || cmdline[i][0] == '-') {
						cerr << "Too few args\n";
						return 1;
					}

					string filenamee (cmdline[i]);

					if (nowOutputFile.is_open()) nowOutputFile.close();

					nowOutputFile.open (filenamee.c_str());

					if (!nowOutputFile.is_open()) {
						cerr << "Failed to open files!\n";
						return -1;
					}

					filename = filenamee;
					useFileout = true;
				}
				else if (app == "-so" || app == "-stdout") {
					if (nowOutputFile.is_open()) nowOutputFile.close();

					if (nowOutputFile.is_open()) nowOutputFile.close();

					useFileout = false;
				}
			}
		}

		for (int i = 1; i < cmdcnt; i++) {
			if (cmdline[i][0] == '-') {
				string app (cmdline[i]);

				strep (j, app) if (app[j] >= 'A' && app[j] <= 'Z') app[j] += 'a' - 'A';

				if (app == "-fo" || app == "-fileout") i++;
			}
			else {
				string nowcmdline (cmdline[i]);

				if (!useFileout) shellworker (cout, GetCmdAppinString (nowcmdline), "");
				else shellworker (nowOutputFile, GetCmdAppinString (nowcmdline), filename);
			}
		}

		return 0;
	}

};
