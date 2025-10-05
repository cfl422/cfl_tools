#ifndef CFL_FILECHECK_H
#define CFL_FILECHECK_H
#include "whr.h"
using namespace std;
namespace Cfl {
	typedef string FileName;
	typedef int CheckerMode_t;
#define FULL_SET 0
#define DESTORY_SPACE_SET 1
#define backstring(s) s[sz(s)-1]
	class FILECHECKER {
		protected:
			CheckerMode_t checkmode;//0:完全一致，1：忽略行首行尾空格
			int line;
		public:
			inline void CheckerModeSet (int Mode) {
				if (Mode >= 0 && Mode <= 1) checkmode = Mode;
			}

		private:
			inline void DestoryBackSpace (string &s) {
				while (!s.empty() && (backstring (s) == ' ' || backstring (s) == '\n' || backstring (s) == '\r')) s.pop_back();
			}

			inline void DestoryHeadSpace (string& s) {
				reverse (all (s));
				DestoryBackSpace (s);
				reverse (all (s));
			}

			inline bool CheckLength (string outstring, string ansstring) {
				int dies = sz (outstring) - sz (ansstring);

				if (dies > 0) printf ("Line %d is too long!\n", line);
				else if (dies < 0) printf ("Line %d is too short!\n", line);

				return dies == 0;
			}

			inline void FileLengthError (int mode) {
				if (mode == 0) printf ("User Output is too short!\n");
				else printf ("User Output is too long!\n");
			}

		protected:
			inline bool CheckString (string outstring, string ansstring) {
				bool ret = true;
				//cout<<outstring<<" "<<ansstring<<" "<<sz(ansstring)<<endl;
				strep (i, ansstring) {
					if (ansstring[i] != outstring[i]) {
						ret = false;
						printf ("Line %d col %d is different : found %c , expected %c !\n", line, i + 1, outstring[i], ansstring[i]);
					}

					//cout<<ansstring[i]<<" "<<outstring[i]<<endl;
				}

				return ret;
			}

			inline bool FileCheck (FileName outputtid, FileName answertid) {
				ifstream output (outputtid.c_str()), answer (answertid.c_str());
				line = 0;
				string outstring = "", ansstring = "";
				bool flag = true;

				while (true) {
					if (!getline (answer, ansstring))break;

					line++;

					if (!getline (output, outstring)) {
						flag = false;
						FileLengthError (0);
						break;
					}

					if (checkmode >= 1) DestoryHeadSpace (ansstring), DestoryHeadSpace (outstring), DestoryBackSpace (ansstring), DestoryBackSpace (outstring);

					flag = flag && CheckLength (outstring, ansstring);
					//cout<<outstring<<" "<<ansstring<<endl;
					//	CheckString(outstring,ansstring);
					bool ccf = CheckString (outstring, ansstring);
					flag = flag && ccf;
				}

				if (getline (answer, ansstring)) FileLengthError (1), flag = false;

				if (flag) printf ("Accepted!");

				return flag;
			}

		public:
			inline bool operator() (FileName outputtid, FileName answertid) {
				return FileCheck (outputtid, answertid);
			}

			inline FILECHECKER() {
				checkmode = 0;
				line = 0;
			}

			inline FILECHECKER (int __checkmode) {
				checkmode = __checkmode;
				line = 0;
			}

			inline FILECHECKER (FileName outputtid, FileName answertid) {
				checkmode = 0;
				line = 0;
				FileCheck (outputtid, answertid);
			}

			inline FILECHECKER (FileName outputtid, FileName answertid, int __checkmode) {
				checkmode = __checkmode;
				line = 0;
				FileCheck (outputtid, answertid);
			}
	};

#undef backstring
};

#endif
