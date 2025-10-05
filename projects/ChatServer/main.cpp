#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <pthread.h>
#include "getip.h"
#include "whr.h"
#include "prostring.h"
using namespace std;
using namespace sock;
using namespace Cfl;
#define sz(s) (int)(s.size())
#define PORT 7070
#define  BUFFER_SIZE 4196
#define _main_send(c) const char* send_data = (c);send(client_socket, send_data, strlen(send_data), 0)
const char *kExitFlag = "下播";
const int maxn = 1002;
pthread_t tid[maxn];
bool flag[maxn];
char server_name[BUFFER_SIZE + 1];
int server_name_len;
SOCKET server_socket;
struct sockaddr_in server_addr;
struct line {
	SOCKET client_socket;
	struct sockaddr_in client_addr;
	char user_name[BUFFER_SIZE + 1];
	int power;
	bool wait;
} client[maxn];

map<string, bool> mp;
queue<int> wait_queue;
char server_public[1];
void _send (SOCKET soc, const char* c, int siz) {
	send (soc, c, siz, 0);
}

//bool check_close;
bool user_accept;
void *admin_server (void* arg) {
a1:
	int zhuang = 0;
	int bian = 0;
	//cout<<bian<<endl;
	inet_ntoa (client[bian].client_addr.sin_addr);
	printf ("成功接收连接: %s\n", client[bian].user_name);
	mp[client[bian].user_name] = 1;
	_send (client[bian].client_socket, server_name, server_name_len);
	char recv_buf[BUFFER_SIZE + 1];

	while (true) {
		//int ret = recv(client[bian].client_socket, client[bian].user_name, BUFFER_SIZE, 0);
//		if (ret < 0) {
//			printf("接收数据失败！\n");
//			break;
//		}
		//client[bian].user_name[ret] = 0; // correctly ends received string
		int ret = recv (client[bian].client_socket, recv_buf, BUFFER_SIZE, 0);

		if (ret < 0) {
			//printf("接收数据失败！\n");
			printf ("<system> 正在关闭服务器...\n");

			//check_close=true;
			for (int i = 1; i <= 1000; i++) if (flag[i]) _send (client[i].client_socket, "已退出连接", strlen ("已退出连接"));

			sleep (3000);
			exit (0);
//			_send (client[0].client_socket, "已退出连接", strlen ("已退出连接"));
		}

		recv_buf[ret] = 0; // correctly ends received string

		//printf("<user/%s> %s \n", client[bian].user_name, recv_buf);
		//if(check_close) _send(client[bian].client_socket,"已更改为系统命令模式",strlen("已更改为系统命令模式"));
		if (check (recv_buf, "-order")) {
			if (client[bian].power < 1) {
				printf ("<Administrator/control> 您没有权限\n");
				_send (client[bian].client_socket, "您没有权限", strlen ("您没有权限"));
				continue;
			}

			zhuang = 1;
			printf ("<Administrator/control> 已更改为系统命令模式\n");
			_send (client[bian].client_socket, "已更改为系统命令模式", strlen ("已更改为系统命令模式"));
		}
		else if (check (recv_buf, "-chat")) {
			zhuang = 0, printf ("<Administrator/control> 已更改为聊天模式\n");
			_send (client[bian].client_socket, "已更改为聊天模式", strlen ("已更改为聊天模式"));
		}
//		else if (check (recv_buf, "-ban")) {
//			zhuang = 0, printf ("<Administrator/control> 请输入\n");
//			_send (client[bian].client_socket, "已更改为聊天模式", strlen ("已更改为聊天模式"));
//		}
		else if (check (recv_buf, "-close")) {
			if (client[bian].power < 2) {
				printf ("<Administrator/control> 您没有权限\n");
				_send (client[bian].client_socket, "您没有权限", strlen ("您没有权限"));
				continue;
			}

			printf ("<Administrator/control> 正在关闭服务器...\n");

			//check_close=true;
			for (int i = 1; i <= 1000; i++) if (flag[i]) _send (client[i].client_socket, "已退出连接", strlen ("已退出连接"));

			sleep (3000);
			_send (client[0].client_socket, "已退出连接", strlen ("已退出连接"));
			exit (0);
		}
		else if (check (recv_buf, "-server/cant_join")) {
			server_public[0] = '0';
			zhuang = 0, printf ("<Administrator/control> 已更改为用户不可加入模式\n");
			_send (client[bian].client_socket, "已更改为用户不可加入模式", strlen ("已更改为用户不可加入模式"));
		}
		else if (check (recv_buf, "-server/private")) {
			server_public[0] = '1';
			zhuang = 0, printf ("<Administrator/control> 已更改为私密模式\n");
			_send (client[bian].client_socket, "已更改为私密模式", strlen ("已更改为私密模式"));
		}
		else if (check (recv_buf, "-server/public")) {
			server_public[0] = '2';
			zhuang = 0, printf ("<Administrator/control> 已更改为公开模式\n");
			_send (client[bian].client_socket, "已更改为公开模式", strlen ("已更改为用户公开模式"));
		}
		else if (check (recv_buf, "-1")) {
			user_accept = 1;

			if (wait_queue.empty()) continue;

			client[wait_queue.front()].wait = false;
			wait_queue.pop();
		}
		else if (check (recv_buf, "-0")) {
			user_accept = 0;

			if (wait_queue.empty()) continue;

			client[wait_queue.front()].wait = false;
			wait_queue.pop();
		}
		else if (zhuang == 0) {
			printf ("<Administrator/chat> \"%s\"\n", recv_buf);

			for (int i = 0; i <= 1000; i++)
				if (flag[i]) {
					string mess = "<Administrator> " + to_string (recv_buf);
					_send (client[i].client_socket, mess.c_str(), strlen (mess.c_str()));
				}

			//_send(client[bian].client_socket,"I see",strlen("I see"));
		}
		else if (zhuang == 1) {
			printf ("<Adminstrator/order> %s\n", recv_buf);
			system (recv_buf);
			_send (client[bian].client_socket, "执行成功", strlen ("执行成功"));
		}

		sleep (5);
	}

	flag[bian] = false;
	//free((int*)arg);
	//cout<<"exit!"<<endl;
	mp[client[bian].user_name] = 0;
	closesocket (client[bian].client_socket);
	return NULL;
}

void *server (void* arg) {
a1:
	char recv_buf[BUFFER_SIZE + 1];
	int zhuang = 0;
	int *p_bian = (int*)arg;
	int bian = *p_bian;
	//cout<<bian<<endl;
	inet_ntoa (client[bian].client_addr.sin_addr);
	//cout<<"accepted!\n"
	_send (client[bian].client_socket, server_public, 1);

	if (server_public[0] == '0') goto back;
	else if (server_public[0] == '1') {
		//_send(client[bian].client_socket,"<system>  请输入验证信息并等待Administrator的同意",strlen("<system> 请输入验证信息并等待Administrator的同意"));
		int ret = recv (client[bian].client_socket, recv_buf, BUFFER_SIZE, 0);

		if (ret < 0) {
			printf ("接收数据失败！\n");
			goto back;
		}

		string mess = "是否允许用户" + to_string (client[bian].user_name) + "加入服务器，验证信息" + to_string (recv_buf) + "(是输入/1，否输入/0)";
		wait_queue.push (bian);
		client[bian].wait = true;
		_send (client[0].client_socket, mess.c_str(), strlen (mess.c_str()));

		while (client[bian].wait) sleep (5);

		if (user_accept) _send (client[bian].client_socket, "1", strlen ("1"));
		else {
			_send (client[bian].client_socket, "0", strlen ("0"));
			goto back;
		}

		//cout<<1<<endl;
	}

	recv (client[bian].client_socket, client[bian].user_name, BUFFER_SIZE, 0);

	while (mp[client[bian].user_name] > 0) {
		_send (client[bian].client_socket, "名字已被用过", 6);
		recv (client[bian].client_socket, client[bian].user_name, BUFFER_SIZE, 0);
	}

	printf ("成功接收连接: %s\n", client[bian].user_name);
	mp[client[bian].user_name] = 1;
	_send (client[bian].client_socket, server_name, server_name_len);

	while (true) {
		int ret = recv (client[bian].client_socket, recv_buf, BUFFER_SIZE, 0);

		if (ret < 0) {
			printf ("接收数据失败！\n");
			break;
		}

		recv_buf[ret] = 0;

		if (check (recv_buf, "-order")) {
			if (client[bian].power < 1) {
				printf ("<user/%s/control> 您没有权限\n", client[bian].user_name);
				_send (client[bian].client_socket, "您没有权限", strlen ("您没有权限"));
				continue;
			}

			zhuang = 1;
			printf ("<user/%s/control> 已更改为系统命令模式\n", client[bian].user_name);
			_send (client[bian].client_socket, "已更改为系统命令模式", strlen ("已更改为系统命令模式"));
		}
		else if (check (recv_buf, "-chat")) {
			zhuang = 0, printf ("<user/%s/control> 已更改为聊天模式\n", client[bian].user_name);
			_send (client[bian].client_socket, "已更改为聊天模式", strlen ("已更改为聊天模式"));
		}
		else if (check (recv_buf, "-exit")) {
			printf ("已退出连接：%s\n", client[bian].user_name);
			_send (client[bian].client_socket, "已退出连接", strlen ("已退出连接"));
			break;
		}
//		else if (check (recv_buf, "-close")) {
//			if (client[bian].power < 2) {
//				printf ("<user/%s/control> 您没有权限\n", client[bian].user_name);
//				_send (client[bian].client_socket, "您没有权限", strlen ("您没有权限"));
//				continue;
//			}
//
//			printf ("<user/%s/control> 正在关闭服务器...\n", client[bian].user_name);
//
//			//check_close=true;
//			for (int i = 1; i <= 1000; i++) _send (client[i].client_socket, "已退出连接", strlen ("已退出连接"));
//
//			sleep (3000);
//			_send (client[0].client_socket, "已退出连接", strlen ("已退出连接"));
//			exit (0);
//		}
		else if (zhuang == 0) {
			printf ("<user/%s/chat> \"%s\"\n", client[bian].user_name, recv_buf);

			for (int i = 0; i <= 1000; i++)
				if (flag[i]) {
					string mess = "<" + to_string (client[bian].user_name) + "> " + to_string (recv_buf);
					_send (client[i].client_socket, mess.c_str(), strlen (mess.c_str()));
				}

			//_send(client[bian].client_socket,"I see",strlen("I see"));
		}
		else if (zhuang == 1) {
			printf ("<user/%s/order> %s\n", client[bian].user_name, recv_buf);
			system (recv_buf);
			_send (client[bian].client_socket, "执行成功", strlen ("执行成功"));
		}

		sleep (5);
	}

back:
	flag[bian] = false;
	//free((int*)arg);
	//cout<<"exit!"<<endl;
	mp[client[bian].user_name] = 0;
	closesocket (client[bian].client_socket);
	return NULL;
}

int main() {
	start_up_setip_h();
	cout << "连接密钥(ip地址)：" << getip() << endl;
	sleep (300);

	server_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server_socket == INVALID_SOCKET) {
		printf ("无法创建服务器套接字!\n");
		return 2;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (PORT);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind (server_socket, (LPSOCKADDR)&server_addr, sizeof (server_addr)) == SOCKET_ERROR) {
		printf ("绑定端口失败!\n");
		return 3;
	}

	if (listen (server_socket, 10)) {
		printf ("无法侦听!\n");
		return 4;
	}

	printf ("请输入服务器名字：");
	scanf ("%s", server_name);
	server_name_len = strlen (server_name);
	string title__ = "title " + to_string (server_name);
	system (title__.c_str());
	server_public[0] = '0';
	sleep (500);
	system ("start ChatClient.exe -admin");
	struct sockaddr_in admin_client_addr;
	int admin_client_addr_len = sizeof (admin_client_addr);
	SOCKET client_socket = accept (server_socket, (SOCKADDR*)&admin_client_addr, &admin_client_addr_len);

	if (client_socket == INVALID_SOCKET) {
		printf ("无法接收!\n");
		return 5;
	}

	//通过结构体向线程函数传入多个参数
	client[0].client_socket = client_socket;
	client[0].client_addr = admin_client_addr;
	client[0].power = 1e9;
	char admin[4197] = "Administrator";
	strcpy (client[0].user_name, admin);
	mp[to_string (admin)] = 1;
	flag[0] = 1;
	int err = pthread_create (tid, NULL, admin_server, NULL);
	pthread_detach (tid[0]);

	if (err != 0)
		exit (err);

	Sleep (100);

	while (true) {
		struct sockaddr_in client_addr;
		int client_addr_len = sizeof (client_addr);
		SOCKET client_socket = accept (server_socket, (SOCKADDR*)&client_addr, &client_addr_len);

		if (client_socket == INVALID_SOCKET) {
			printf ("无法接收!\n");
			continue;
		}

		//通过结构体向线程函数传入多个参数
client_accepted:
		int available = -1;

		for (int i = 1; i <= 1000; i++) if (!flag[i]) {
				flag[i] = true, available = i;
				break;
			}

		if (available == -1) {
			sleep (1000);
			goto client_accepted;
		}

		client[available].client_socket = client_socket;
		client[available].client_addr = client_addr;
		int *p_available = &available;
		int err = pthread_create (tid + available, NULL, server, (void*)p_available);
		pthread_detach (tid[available]);

		if (err != 0)
			exit (err);

		Sleep (100);
	}

	closesocket (server_socket);
	WSACleanup();
	return 0;
}
