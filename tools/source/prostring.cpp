#include "whr.h"
#include "prostring.h"
namespace Cfl {
	bool DLLIMPORT check (char c[], string s) {
		int sl = strlen (c);

		if (sl != sz (s)) return false;

		for (int i = 0; i < sl; i++)
			if ((i >= sz (s) && (c[i] != '\0' && c[i] != ' ' && c[i] != '\n')) || (i < sz (s) && c[i] != s[i]))
				return false;

		return true;
	}

	string DLLIMPORT to_string (char c[]) {
		int sl = strlen (c);
		string s;

		for (int i = 0; i < sl; i++) s += c[i];

		return s;
	}
};

string DLLIMPORT chartostring (char* a) {
	string ret;

	for (int i = 0; i < (int)strlen (a); i++) ret += a[i];

	return ret;
}
