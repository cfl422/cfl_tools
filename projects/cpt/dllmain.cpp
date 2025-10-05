
#include "cpt.h"
#ifndef IS_DLLEXPORT
	#error
#endif
namespace Cfl {
	CPT_STRING DLLIMPORT getcpt (string rf) {
		CPT_STRING s, ret;
		ifstream readfile ((rf).c_str());

		while (getline (readfile, s))
			ret += s;

		return ret;
	}

	template<int len>
	string  CPTlist<len>::get_string (string str, int &i, char endd) {
		string ret = "";

		for (; i < str.size(); i++) {
			if (str[i] == endd) return ret;

			ret += str[i];
		}

		return ret;
	}

	template <int len> ll  CPTlist<len>::string_to_int (string s) {
		ll ret = 0;
		strep (i, s) ret = ret * 10 + s[i] - '0';
		return ret;
	}

	template <int len> int  CPTlist<len>::v_string_to_list (CPT_STRING str, int &i, bool can_title) {
		string key;
		int cptwei = 1;

		if (!can_title) {
			tot++;
			cptwei = tot;
		}

		for (; i < (int)str.size(); i++) {
			if (str[i] == '[') {
				i++;
				key = get_string (str, i, ']');
			}
			else if (str[i] == '\"') {
				i++;
				string get = get_string (str, i, '\"');

				if (key == "name") cptlist[cptwei].name = get;
				else if (key == "describle") cptlist[cptwei].describle = get;
				else if (key == "setting") cptlist[cptwei].setting = string_to_int (get);
				else if (key == "title" && can_title) title = get;
				else if (key == "filedescrible" && can_title) filedescrible = get;
			}
			else if (str[i] == '{') {
				if (key == "list") {
					i++;
					cptlist[cptwei].sonlist.push_back (v_string_to_list (str, i, false));
				}
			}
			else if (str[i] == '}') return cptwei;
		}

		return cptwei;
	}

	template<int len>
	void  CPTlist<len>::v_print (int wei, int ceng) {
//		cout<<cptlist[wei].setting<<endl;
		if (! (cptlist[wei].setting & can_look)) return;

//		cout<<wei<<" "<<ceng<<" ";
		spacee;
		cout << cptlist[wei].name;

		if (!cptlist[wei].sonlist.empty()) cout << ">";

		cout << endl;
		strep (i, cptlist[wei].sonlist) {
//			cout<<cptlist[wei].sonlist[i]<<endl;
			v_print (cptlist[wei].sonlist[i], ceng + 1);
		}
	}

	template<int len> void CPTlist<len>::reset() {
		for (int i = 1; i <= len; i++) {
			cptlist[i].name = "", cptlist[i].describle = "";
			cptlist[i].sonlist.clear();
			cptlist[i].setting = can_look | can_write;
			cptlist[i].zhan = false;
		}

		tot = 1;
		cptlist[1] = cptlistNode{"<cpt>", "root", can_look, true};
	}

	template<int len> void  CPTlist<len>::string_to_list (CPT_STRING str) {
		int qi = 0;
		v_string_to_list (str, qi, true);
	}

	template<int len>
	void  CPTlist<len>::print() {
//		system (("title cpt_" + title).c_str());
		cout << "title : " << title << "\n" << "describle : " << filedescrible << "\n";
		v_print (1, 0);
	}
};
