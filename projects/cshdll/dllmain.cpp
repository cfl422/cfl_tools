/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include "head.h"
//#include <windows.h>
using namespace std;
namespace Cfl {
	int DLLIMPORT builtin_system (string command) {
		string cmd;
		cmd = "\"";

		for (int i = 0; i < (int)command.size(); i++) {
			if (command[i] == '&') {
				if (i == 0 || command[i - 1] != '&') cmd += "\" \"";
			}
			else cmd += command[i];
		}

		cmd += '\"';
		cmd = " " + cmd + " " ;
//		char c[8192];
//		strep (i, cmd) c[i] = cmd[i];
		//fixme
		char cdcd = '\0';
		char *pcdcd = &cdcd;
		char **api = &pcdcd;
		bool flag = false;
		int ge = 0;
		int cmdcnt = 0, zshcnt = 0;
		strep (i, cmd) {
			if (cmd[i] == '\"') {
				if (!ge && (i == 0 || cmd[i - 1] == ' '))flag = !flag;
				else {
					if (ge) ge--;
					else ge++;

					api[cmdcnt][zshcnt++] = '\"';
				}
			}
			else if (cmd[i] == ' ') {
				if (flag)
					api[cmdcnt][zshcnt++] = ' ';
				else {
					if (i == 0 || cmd[i - 1] != ' ') {
						cmdcnt++;
						zshcnt = 0;
					}
				}
			}
			else api[cmdcnt][zshcnt++] = cmd[i];
		}

//		return 0;
		cerr << "connect successfully!\n";
		return shellserver (cmdcnt, api);
	}
}

BOOL WINAPI DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH: {
				break;
			}

		case DLL_PROCESS_DETACH: {
				break;
			}

		case DLL_THREAD_ATTACH: {
				break;
			}

		case DLL_THREAD_DETACH: {
				break;
			}
	}

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
