#include "ShellBasicServices.h"
namespace Cfl {
	namespace Shell_BasicServices {
		void pause() {
			printf ("请按任意键继续……\n");
			char c = getch();
		}


		string pwd() {
			char path[MAX_PATH];

			if (!GetCurrentDirectory (MAX_PATH, path)) {
				std::cerr << "无法获取当前目录" << std::endl;
				return "";
			}

			return chartostring (path);
		}

		int dir (ostream& out) {
			// 获取当前目录的路径
			string path = Shell_BasicServices::pwd();

			// 构造搜索模式，例如 "*.*" 表示所有文件
			std::string searchPath = path + "\\*.*";
			out << "Now path : " << path << endl;
			// 初始化 FindFileData 结构体
			WIN32_FIND_DATA findFileData;
			HANDLE hFind = FindFirstFile (searchPath.c_str(), &findFileData);

			if (hFind == INVALID_HANDLE_VALUE) {
				std::cerr << "无法打开目录" << std::endl;
				return 1;
			}

			do {
				// 检查是否是文件（非目录）
				if ( (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					out << "[Dir]       " << findFileData.cFileName << std::endl;

//				else out << "[Dir]          " << findFileData.cFileName << std::endl;
			}
			while (FindNextFile (hFind, &findFileData) != 0);

			// 检查是否有错误发生（除了最后一个文件外）
			if (GetLastError() != ERROR_NO_MORE_FILES) {
				std::cerr << "读取文件时出错" << std::endl;
				FindClose (hFind);
				return 1;
			}

			hFind = FindFirstFile (searchPath.c_str(), &findFileData);

			if (hFind == INVALID_HANDLE_VALUE) {
				std::cerr << "无法打开目录" << std::endl;
				return 1;
			}

			do {
				// 检查是否是文件（非目录）
				if ( ! (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					out << "[File]      " << findFileData.cFileName << std::endl;

//				else out << "[Dir]          " << findFileData.cFileName << std::endl;
			}
			while (FindNextFile (hFind, &findFileData) != 0);

			// 检查是否有错误发生（除了最后一个文件外）
			if (GetLastError() != ERROR_NO_MORE_FILES) {
				std::cerr << "读取文件时出错" << std::endl;
				FindClose (hFind);
				return 1;
			}

			FindClose (hFind);
			return 0;
		}

		int cd (string path) {
			return SetCurrentDirectory (path.c_str());
		}

		void exit() {
			std::exit (0);
		}

		void echo (ostream& ost, string str) {
			ost << str;
		}
	};
};
