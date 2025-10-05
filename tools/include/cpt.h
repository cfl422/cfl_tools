#ifndef CFL_CPT_H
#define CFL_CPT_H
//#define BUILDING_DLL 1
#if BUILDING_DLL
	#define DLLIMPORT __declspec(dllexport)
	#define IS_DLLEXPORT
#else
	#define DLLIMPORT __declspec(dllimport)
#endif
#include "whr.h"
namespace Cfl {
	typedef string __CPT_STRING;
	typedef __CPT_STRING CPT_STRING;
	CPT_STRING DLLIMPORT getcpt (string rf) ;

#define can_look 1
#define can_write 2
	class DLLIMPORT cptlistNode {
		public:
			string name, describle;
			ll setting = 0;
			bool zhan = false;
			vector<int> sonlist;
	} ;

//#ifndef IS_DLLEXPORT
//	#error The code has not define dllexport
//#endif
	template<int len>
	class DLLIMPORT CPTlist {
		public:
			cptlistNode cptlist[len + 2];

			int tot = 1;
			string title;
			string filedescrible;
		private:
			string   get_string (string str, int &i, char endd) ;

			ll   string_to_int (string s) ;

			int v_string_to_list (CPT_STRING str, int &i, bool can_title);

#define spacee for(int i=1;i<=ceng;i++) cout<<"  ";
			void  v_print (int wei, int ceng) ;

		public:
			void reset() ;

			void string_to_list (CPT_STRING str) ;

			void print();
	};

};

#endif
