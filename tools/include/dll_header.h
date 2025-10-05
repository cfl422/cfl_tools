#ifndef DLLIMPORT
	#if BUILDING_DLL
		#define DLLIMPORT __declspec(dllexport)
		#define IS_DLLEXPORT
	#else
		#define DLLIMPORT __declspec(dllimport)
	#endif
#endif
