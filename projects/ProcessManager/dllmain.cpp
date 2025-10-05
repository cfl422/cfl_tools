#include "ProcessCreater.h"
#include <windows.h>
using namespace std;

namespace Cfl {
	int DLLIMPORT CCreateProcessIdle (char* commandLine) {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		// 初始化STARTUPINFO结构体
		ZeroMemory (&si, sizeof (si));
		si.cb = sizeof (si);
		ZeroMemory (&pi, sizeof (pi));

		// 创建进程的命令行参数和应用程序名
//		char appName[] = "notepad.exe"; // 注意：路径可以是绝对路径或相对路径，也可以是应用程序名（如果它在系统的PATH中）
//		char commandLine[] = "notepad.exe"; // 可选，如果为NULL，则使用appName

		// 创建进程
		if (!CreateProcess (NULL,  // 使用命令行参数，而不是应用程序名（NULL表示使用commandLine）
		                    commandLine, // 命令行参数
		                    NULL,       // 进程句柄不可继承
		                    NULL,       // 线程句柄不可继承
		                    FALSE,      // 设置句柄继承选项
		                    0,          // 不使用特殊的创建标志
		                    NULL,       // 使用父进程的环境块
		                    NULL,       // 使用父进程的起始目录
		                    &si,        // 指向STARTUPINFO结构
		                    &pi)        // 接收进程信息
		   ) {
			std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
			return -1;
		}
		else {
#ifdef  OUTPUT_PROCESS_CREATER_LOGS
			std::cout << "Process created successfully. Process ID: " << pi.dwProcessId << std::endl;
#endif
		}

		// 等待子进程结束
		WaitForSingleObject (pi.hProcess, INFINITE);

		// 关闭进程和线程句柄
		CloseHandle (pi.hProcess);
		CloseHandle (pi.hThread);

		return 0;
	}

	void *PthrCCreateProcess (void* arg) {
		char *z = (char*)arg;
#ifdef OUTPUT_PROCESS_CREATER_LOGS
		printf ("Command : %s !\n", z);
#endif
		static int ret = CCreateProcessIdle (z);
		return (void*) (&ret);
	}

	int DLLIMPORT CCreateProcess (char* command) {
		pthread_t tid;
		pthread_create (&tid, NULL, PthrCCreateProcess, (void*)command);
		pthread_detach (tid);
#ifdef OUTPUT_PROCESS_CREATER_LOGS
		printf ("new process create successfully!\n");
#endif
		return 0;
	}

//	int DLLIMPORT CNTCreateProcess() {
//		HMODULE ntdll = LoadLibrary ("ntdll.dll");
//		NtCreateUserProcess NtCreateUserProcessFunc = (NtCreateUserProcess)GetProcAddress (ntdll, "NtCreateUserProcess");
//
//		if (NtCreateUserProcessFunc) {
//			HANDLE hProcess, hThread;
//			NTSTATUS status = NtCreateUserProcessFunc (
//			                      &hProcess, &hThread, MAXIMUM_ALLOWED, MAXIMUM_ALLOWED, NULL, NULL, 0, 0, NULL, 0, 0);
//
//			if (status == STATUS_SUCCESS) {
//				// 成功创建进程和线程
//				CloseHandle (hProcess);
//				CloseHandle (hThread);
//			}
//			else {
//				// 错误处理
//				printf ("Failed to create process: %lu\n", status);
//				return 1;
//			}
//		}
//		else {
//			printf ("Failed to load NtCreateUserProcess\n");
//			return -1;
//		}
//	}
};

//int (*CCreateProcess) (char*);
//int (*CCreateProcessIdle) (char*);
void installNowDll (HINSTANCE hinstDLL) {
//	CCreateProcess = (int (char*))GetProcAddress (hinstDLL, "__CCreateProcess");
//	CCreateProcessIdle = (int (char*))GetProcAddress (hinstDLL, "__CCreateProcessIdle");
}

//using namespace Cfl;
BOOL WINAPI DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH: {
				installNowDll (hinstDLL);
				break;
			}

		case DLL_PROCESS_DETACH: {
				break;
			}

		case DLL_THREAD_ATTACH: {
				break;
			}

		case DLL_THREAD_DETACH: {
				break;
			}
	}

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
