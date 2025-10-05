#ifndef CFL_CHECKER_H
#define CFL_CHECKER_H
#include "check.h"
//#include "prostring.h"
#include <windows.h>
//#include "cpt/dll.h"
namespace Cfl {
#define dirPath "C:\\Cfl\\Library\\Checker\\registers\\in"+sid+".txt"
	class CHECKER {
		protected:
			inline int Process (int id, string datamaker, string stdsource, string baoli, int ci = -1, int * endflag = NULL) {
				FILECHECKER fc (DESTORY_SPACE_SET);
				string sid ( std::to_string (id));
				system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt").c_str());
				system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\ans" + sid + ".txt").c_str());
				system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt").c_str());
				int zu = 0;
				datamaker += " > C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";
				stdsource += " > C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt < C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";
				baoli += " > C:\\Cfl\\Library\\Checker\\registers\\ans" + sid + ".txt < C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";

				while (ci--) {
					printf ("Checker id %d\n", id);
					zu++;
					system (datamaker.c_str());
					system (baoli.c_str());
					cout << "Running on test " << zu << " :\n";
					int tim = clock();
					system (stdsource.c_str());
					cout << "runtime:" << " " << clock() - tim << endl;

					if (!fc ("C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt", "C:\\Cfl\\Library\\Checker\\registers\\ans" + sid + ".txt"))
						system ("pause");

					if (endflag) return 0;
				}

				return 0;
			}

		public:
			inline int operator() (int id, string datamaker, string stdsource, string baoli, int ci = -1, int * endflag = NULL) {
				return Process (id, datamaker, stdsource, baoli, ci, endflag);
			}
	};

	class TIMEFINDER {
		protected:
			inline int process (int id, string datamaker, string stdsource, int ci = -1, int * endflag = NULL) {
//	FILECHECKER fc (DESTORY_SPACE_SET);
				int zu = 0;
				string sid  ( std::to_string (id));
				system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt").c_str());
				system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\ans" + sid + ".txt").c_str());
				system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt").c_str());
				datamaker += " > C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";
				stdsource += " > C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt < C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";

//	datamaker+=" < C:\\Cfl\\Library\\Checker\\registers\\ans"+sid+".txt < C:\\Cfl\\Library\\Checker\\registers\\in"+sid+".txt";
				while (ci--) {
					printf ("TimeFinder id %d\n", id);
					zu++;
					system (datamaker.c_str());
//		system(baoli.c_str());
					cout << "Running on test " << zu << " :\n";
					int tim = clock();
					system (stdsource.c_str());
//		if(!FileCheck("C:\\Cfl\\Library\\Checker\\registers\\out"+sid+".txt","C:\\Cfl\\Library\\Checker\\registers\\ans"+sid+".txt")){
//			system("pause");
//		}
					cout << "runtime:" << " " << clock() - tim << endl;

					if (endflag) return 0;
				}

				return 0;
			}

		public:
			inline int operator() (int id, string datamaker, string stdsource, int ci = -1, int * endflag = NULL) {
				return process (id, datamaker, stdsource, ci, endflag);
			}
	};
};

/*
int CheckerProcessEx (FileName Configfile) {
	CheckerModeSet (DESTORY_SPACE_SET);
	CPTlist<1000> config;
	config.reset();
	config.string_to_list (getcpt (Configfile));
//	string sid = to_string (id);
//	system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt").c_str());
//	system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\ans" + sid + ".txt").c_str());
//	system (("type nul > C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt").c_str());
//	int zu = 0;
//	datamaker += " > C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";
//	stdsource += " > C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt < C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";
//	baoli += " > C:\\Cfl\\Library\\Checker\\registers\\ans" + sid + ".txt < C:\\Cfl\\Library\\Checker\\registers\\in" + sid + ".txt";
//
//	while (ci--) {
//		printf ("Checker id %d\n", id);
//		zu++;
//		system (datamaker.c_str());
//		system (baoli.c_str());
//		cout << "Running on test " << zu << " :\n";
//		int tim = clock();
//		system (stdsource.c_str());
//		cout << "runtime:" << " " << clock() - tim << endl;
//
//		if (!FileCheck ("C:\\Cfl\\Library\\Checker\\registers\\out" + sid + ".txt", "C:\\Cfl\\Library\\Checker\\registers\\ans" + sid + ".txt"))
//			system ("pause");
//
//		if (endflag) return 0;
//	}

	return 0;
}
*/
#endif
