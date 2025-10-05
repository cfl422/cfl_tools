#include "prostring.h"
using namespace std;
string chartostring (char* a) {
	string ret;

	for (int i = 0; i < (int)strlen (a); i++) ret += a[i];

	return ret;
}
