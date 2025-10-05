#ifndef CFL_SHELLBASICSERVICES_H
#define CFL_SHELLBASICSERVICES_H
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "prostring.h"
using namespace std;
#ifndef cflvsafgasdgf
#define cflvsafgasdgf
namespace Cfl {
	namespace Shell_BasicServices {
		void pause() ;

		string pwd() ;

		int dir (ostream& out) ;
		int cd (string path) ;

		void exit() ;

		void echo (ostream& ost, string str);
	};
};

#endif

#endif
