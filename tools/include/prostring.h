#pragma once
#ifndef PROSTRING_H
#define PROSTRING_H
#include "whr.h"
using namespace std;
string DLLIMPORT chartostring (char* a) ;
namespace Cfl {
	bool DLLIMPORT check (char c[], string s);
	string DLLIMPORT to_string (char c[]);
};

#endif
