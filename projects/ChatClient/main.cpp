#include <bits/stdc++.h>
#include <winsock2.h>
#include <windows.h>
#include <pthread.h>
#include "getip.h"
#include "conio.h"
#include "whr.h"
#include "prostring.h"
// #include "uwing.h"
#define PORT 7070
#define BUFFER_SIZE 4196
#define sleep Sleep
using namespace std;
using namespace sock;
#define line Line
int line = 0;
const char *kExitFlag = "下播";
char SERVER_IP[BUFFER_SIZE + 1];
char inputstring[BUFFER_SIZE + 1];
SOCKET client_socket;
string message;
bool data1 (SOCKET client_socket, char data[]) {
	if (send (client_socket, data, strlen (data), 0) < 0) {
		printf ("发送数据失败!\n");
		line++;
		return false;
	}

	return true;
}

string s;
char user_name[BUFFER_SIZE + 1];
char server_name[4197];
char tzy[4197];
bool life_check, input_check;
vector<string> huan;
const int minx = 30, miny = 15;
bool check_output;
struct Order {
	string ord;
	pair<string, int> son[102];
} order[1002];

mt19937 rnd (time (0)^clock());
int random (int l, int r) {
	return rnd() % (r - l + 1) + l;
}

void gotoxy (int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), pos);
}

bool admin_flag = false;
// using namespace uwing;
// void output_rect(int x1,int y1,int x2,int y2,int cu,COLORREF backcolor,COLORREF linecolor=RGB(0,0,0)){
// 	//if(linecolor==RGB(-1,0,0)) linecolor=backcolor;
// 	setlinestyle(PS_SOLID, cu);
// 	setfillcolor(backcolor);
// 	fillrectangle(x1,y1,x2,y2);
// 	setlinecolor(linecolor);
// 	if(cu>0) rectangle(x1,y1,x2,y2);
// }
// void Moban_reading_window(){
// //	initgraph(800,600);
// 	//RECT r={0,0,800,100};
// 	output_rect(60,1,800,100,-1,SUPER);
// 	output_rect(1,1,60,600,-1,ULTRA,ULTRA);
// 	output_rect(740,100,800,520,-1,0xAAAA55,0xAAAA55);
// 	output_rect(60,520,800,600,-1,CYAN,CYAN);
// }
// void moban_init_window(bool flag=true){
// 	cls;
// 	set_word_color(RGB(0,0,0));
// 	if(flag) Moban_reading_window();
// 	Word::init_word();
// }
void *input (void* arg) {
	char data[BUFFER_SIZE + 1];
	int len = -1, laslen = -1;
	mem (data, 0);
	bool flaggggg = true;


	while (true) {
		if (kbhit()) {
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
			COORD cursorPosition = csbi.dwCursorPosition;
			gotoxy (0, cursorPosition.Y);
			//mem(data, 0);
			char da;
			da = getch();

			if (!flaggggg) {
				flaggggg = true;
				continue;
			}

			//cout<<da<<" ";
			if ((long long)da == -32) {
				flaggggg = false;
				continue;
			}

			if (da == VK_BACK || da == VK_DELETE) data[len--] = 0;
			else if (da == VK_ESCAPE) {
				len = -1;
				mem (data, 0);
			}
			else if (da == VK_RETURN) {
				data1 (client_socket, data);
				mem (data, 0);
				len = -1;
			}
			else if (da >= 32 && da != 127)
				data[++len] = da;

			printf ("%s", data);

			for (int i = len + 1; i <= laslen; i++) cout << " ";

			laslen = len;
		}
		else if (check_output) {
			check_output = false;
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
			COORD cursorPosition = csbi.dwCursorPosition;
			gotoxy (0, cursorPosition.Y);
			printf ("%s", data);

			for (int i = len + 1; i <= laslen; i++) cout << " ";

			laslen = len;
		}

		sleep (5);
	}

	return NULL;
}

char recv_data[BUFFER_SIZE + 1];
void *output (void* arg) {
	if (admin_flag)cout << "<system> you have the highest power of the server" << endl;

	while (true) {
		if (!life_check) break;

		mem (recv_data, 0);
		int ret = recv (client_socket, recv_data, BUFFER_SIZE, 0);

		if (ret < 0) {
			printf ("无法接收数据!\n");
			line++;
			break;
		}

		recv_data[ret] = 0;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
		COORD cursorPosition = csbi.dwCursorPosition;
		gotoxy (0, cursorPosition.Y);

		if (recv_data[0] != '<') {
			message += "<server/return> \"" + Cfl::to_string (recv_data) + "\"\n";
			printf ("<server/return> \"%s\"\n", recv_data);

			if (Cfl::check (recv_data, "已退出连接")) {
				if (!admin_flag)break;
				else {
					sleep (1000);
					printf ("<system> server is close");
					sleep (3000);
					exit (0);
				}
			}
		}
		else printf ("%s\n", recv_data), message += Cfl::to_string (recv_data) + "\n";

		line++;
		check_output = true;
	}

	return NULL;
}

int init_Client (int argc, char** argv) {
	if (argc >= 2) {
		string asds (argv[1]);

		if (asds == "-admin") admin_flag = true;
	}

	return 0;
}

int main (int argc, char** argv) {
	if (init_Client (argc, argv)) {
		cerr << "Fail to init chat client!\n";
		return -1;
	}

	start_up_setip_h();

	if (!admin_flag) {
		system ("title client");
		// SIMPLEWINDOW::InitWindow(600,450,RGB(255,255,255));
		//slp(500);
		//SIMPLEWINDOW::InitWindow(800,600,RGB(255,255,255));
//	moban_init_window();
		// Word::init_word();
		// MOUSE::InitMouse();
		// INPUTBOX::InitBoxInput();
		// moban_init_window(false);
		// //slp(500);
		// //slp(5000);
		// Word::v_output(20,20,"输入你的名字：");
		printf ("请输入你的名字：\n");
		// WordRectID rett= WordRect::create_WordRect(20,80,RGB(0,0,0),LEGENDARY,MYTHIC,"ygg");
		// display_WordRect();
		// slp(1000);
		// display_WordRect();
		// WordRect::insert_text(rett,"pls");
		// display_WordRect();
//	InputBoxID inputname=INPUTBOX::create_InputBox(20,80,RGB(0,0,0),RGB(255,0,0),RGB(255,255,255),MYTHIC);
//	display_InputBox(inputname);
//	char* InputBoxret=GetInputMessage(inputname);
//	for(int i=0;i<strlen(InputBoxret);i++) user_name[i]=InputBoxret[i];
//	InputBox(inputstring, BUFFER_SIZE, TEXT("请输入半径"));

		line++;
		scanf ("%s", user_name);
		line++;
		string title__ = "title client/" + Cfl::to_string (user_name);
		system (title__.c_str());
	}
	else {
		string __user_name = "Administrator";
		strep (i, __user_name) user_name[i] = __user_name[i];
		string title__ = "title " + Cfl::to_string (user_name);
		system (title__.c_str());
	}

//	system ("pause");

	while (true) {
a1:
		cls;
		message = "";

		if (!admin_flag) {
			cout << "温馨提示：" << endl;
			cout << "ip地址：" << getip() << endl;
			printf ("输入密钥: ");
			scanf ("%s", SERVER_IP);
			line += 3;
//	printf("输入名称: ");
//	scanf("%s", user_name);
			// 初始化socket dll。
		}
		else {
			strcpy (SERVER_IP, getip().c_str());
//			line+=3;
		}

		client_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (client_socket == INVALID_SOCKET) {
			printf ("无法创建服务器套接字!\n");
			line++;
			continue;
		}

		struct sockaddr_in server_addr;

		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons (PORT);
		server_addr.sin_addr.S_un.S_addr = inet_addr (SERVER_IP);

		if (connect (client_socket, (LPSOCKADDR)&server_addr, sizeof (server_addr)) == SOCKET_ERROR) {
			printf ("无法连接服务器: %ld !\n", GetLastError());
			line++;
			continue;
		}

//	int accept_join=recv(client_socket, tzy, BUFFER_SIZE, 0);
//	if(accept_join>=0){printf("%s\n",tzy);goto a1;}
		int ret = recv (client_socket, recv_data, BUFFER_SIZE, 0);

		if (ret < 0) {
			printf ("无法接收数据!\n");
			line++;
			continue;
		}

		if (!admin_flag) {
			if (recv_data[0] == '0') {
				printf ("<system> 此服务器为私有服务器，不可加入!\n");
				slp (2000);
				continue;
			}
			else if (recv_data[0] == '1') {
				printf ("<system>  此服务器为私有服务器，请输入验证信息并等待Administrator的同意(不要输入空格):");
				char yan[120];
				scanf ("%s", yan);

				if (!data1 (client_socket, yan)) continue;

				int ret = recv (client_socket, recv_data, BUFFER_SIZE, 0);

				if (ret < 0) {
					printf ("无法接收数据!\n");
					line++;
					slp (1000);
					continue;
				}

				//printf("%s\n",recv_data);
				if (recv_data[0] == '1') printf ("成功加入服务器！\n");
				else {
					printf ("未获得Administrator的同意!\n");
					slp (2000);
					continue;
				}
			}
			else printf ("<system> 已加入服务器");

			if (!data1 (client_socket, user_name)) {
				cerr << "无法发送数据！\n";
				slp (1000);
				continue;
			}




			ret = recv (client_socket, server_name, BUFFER_SIZE, 0);
		}
		else if (!data1 (client_socket, "Server is running"))
			return -1;


		if (ret < 0) {
			printf ("无法接收数据!\n");
			line++;
			slp (1000);
			continue;
		}

		server_name[ret] = 0;

		if (!admin_flag) {
			while (Cfl::check (server_name, "名字已被用过")) goto a1;

			printf ("连接成功!服务器名称：%s\n", server_name);
			getchar();
		}
		else
			printf ("<Administrator> 服务器名称：%s\n", server_name);

		slp (2000);

		line++;

		cls;
		pthread_t tid1, tid2;
		life_check = true;
		int err = pthread_create (&tid1, NULL, input, NULL);
		int err2 = pthread_create (&tid2, NULL, output, NULL);

		if (err != 0) exit (err);

		if (err2 != 0) exit (err2);

		pthread_detach (tid1);
		pthread_join (tid2, NULL);
		life_check = false;
	}

	closesocket (client_socket);
	WSACleanup();
	system ("pause");
	return 0;
}
