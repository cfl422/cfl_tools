#include "ApplicationOperations.h"
namespace Cfl {
	string DLLIMPORT getAppType (string appname) {
		reverse (all (appname));
		string typen = "";
		bool flag = false;
		strep (i, appname) {
			if (appname[i] == '\\' || appname[i] == '/') break;

			if (appname[i] == '.') {
				flag = true;
				break;
			}

			typen = appname[i] + typen;
		}

		if (flag) return typen;

		return "";
	}
};
