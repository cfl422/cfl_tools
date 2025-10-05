#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
	#define DLLIMPORT __declspec(dllexport)
#else
	#define DLLIMPORT __declspec(dllimport)
#endif
#include <bits/stdc++.h>
using namespace std;
namespace Cfl {
	int DLLIMPORT system (string command);
};

#endif
