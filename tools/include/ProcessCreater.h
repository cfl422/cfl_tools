#ifndef PROCESSCREATER_H
#define PROCESSCREATER_H
#include <windows.h>
#include <bits/stdc++.h>
#include <ntstatus.h>
#include <winternl.h>
#if BUILDING_DLL
	#define DLLIMPORT __declspec(dllexport)
#else
	#define DLLIMPORT __declspec(dllimport)
#endif
//#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)

//typedef NTSTATUS (NTAPI* NtCreateUserProcess) (
//    _Out_ PHANDLE ProcessHandle,
//    _Out_ PHANDLE ThreadHandle,
//    _In_ ACCESS_MASK ProcessDesiredAccess,
//    _In_ ACCESS_MASK ThreadDesiredAccess,
//    _In_opt_ POBJECT_ATTRIBUTES ProcessObjectAttributes,
//    _In_opt_ POBJECT_ATTRIBUTES ThreadObjectAttributes,
//    _In_ ULONG ProcessFlags,
//    _In_ ULONG ThreadFlags,
//    _In_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
//    _Inout_ PS_CREATE_INFO CreateInfo,
//    _In_ PPS_ATTRIBUTE_LIST AttributeList
//);
namespace Cfl {
	int  DLLIMPORT CCreateProcessIdle (char* commandLine) ;

	int DLLIMPORT CCreateProcess (char* command) ;

//	int DLLIMPORT CNTCreateProcess();
};

#endif
