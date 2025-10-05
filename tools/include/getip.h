#ifndef GETIP_H
#define GETIP_H
#include "whr.h"

//#pragma comment(lib, "WS2_32.lib")

namespace sock {
	SOCKET make_up_server() ;

	void  make_up_server (SOCKET& server_socket) ;
	std::string  getip() ;

	void  start_up_setip_h() ;

	void  unblocking (SOCKET& sock) ;
};

#endif
