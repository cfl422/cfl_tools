#ifndef CSYSTEM_BUILTIN_H
#define CSYSTEM_BUILTIN_H

#include <bits/stdc++.h>
#include <windows.h>
#if BUILDING_DLL
	#define DLLIMPORT __declspec(dllexport)
#else
	#define DLLIMPORT __declspec(dllimport)
#endif
using namespace std;
namespace Cfl {
	int DLLIMPORT builtin_system (string command);
};

#endif
