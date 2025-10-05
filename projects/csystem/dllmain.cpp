/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include "ProcessCreater.h"

#include <windows.h>
#define strep(i,s) for(int i=0;i<(int)s.size();i++)
namespace Cfl {
	int DLLIMPORT system (string command) {
		string cmd;
		cmd = "\"";

		for (int i = 0; i < (int)command.size(); i++) {
			if (command[i] == '&') {
				if (i == 0 || command[i - 1] != '&') cmd += "\" \"";
			}
			else cmd += command[i];
		}

		cmd += '\"';
		char c[8192];
		cmd = "csh.exe " + cmd;
		strep (i, cmd) c[i] = cmd[i];
		return CCreateProcessIdle (c);
	}
};

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
