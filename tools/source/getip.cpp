#include "getip.h"
namespace sock {
	SOCKET  DLLIMPORT make_up_server() {
		SOCKET server_socket;
		server_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (server_socket == INVALID_SOCKET) {
			printf ("无法创建服务器套接字!\n");
			exit (2);
		}

		return server_socket;
	}

	void DLLIMPORT make_up_server (SOCKET& server_socket) {
		server_socket = make_up_server();
	}

	std::string DLLIMPORT  getip() {
		WSADATA WSAData;
		char hostName[256];

		if (!gethostname (hostName, sizeof (hostName))) {
			hostent *host = gethostbyname (hostName);

			if (host != NULL) return inet_ntoa (* (struct in_addr * ) * host->h_addr_list);
		}

		return "Get IP failed.";
	}

	void  DLLIMPORT start_up_setip_h() {
		WSADATA wsa_data;

		if (WSAStartup (MAKEWORD (2, 2), &wsa_data) != 0) {
			printf ("初始化套接字dll失败!\n");
			exit (1);
		}
	}

	void DLLIMPORT unblocking (SOCKET& sock) {
		u_long mode = 1;

		if (ioctlsocket (sock, FIONBIO, &mode) != 0) {
			closesocket (sock);
			printf ("Socket unblocking failed!!!");
			exit (6);
		}
	}
};
