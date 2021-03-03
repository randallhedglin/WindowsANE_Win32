//
//  WindowsANE.h
//

#ifndef WindowsANE_WindowsANE_h
#define WindowsANE_WindowsANE_h

// windows includes //

#include <WinSDKVer.h> // load version flags

// set version flags (Win 8.1)
#define NTDDI_VERSION NTDDI_WINBLUE
#define _WIN32_WINNT  _WIN32_WINNT_WINBLUE
#define WINVER        _WIN32_WINNT_WINBLUE

#include <sdkddkver.h> // apply version flags

#define WIN32_LEAN_AND_MEAN // keep it light

#include <Windows.h> // basic Windows components

// Flash includes //

#include "FlashRuntimeExtensions.h"

// function type definition //

#ifdef __cplusplus
	#define WINDOWSANE_API extern "C" __declspec(dllexport)
#else
	#define WINDOWSANE_API __declspec(dllexport)
#endif // __cplusplus

// macros //

// DEBUG_MSG() -- display message box with debug string
#define DEBUG_MSG(msg) MessageBox(NULL, msg, TEXT("DEBUG_MSG"), MB_OK);

// SAFE_FREE() -- safe release of memory pointers
#define SAFE_FREE(mem) if(mem) { free((void*) mem); mem = NULL; }

// constants //

// number of windows to hold in search results
#define HWNDSEARCH_NUM 6

// structures //

// structure for searching windows
typedef struct _HWNDSEARCH
{
	// process id
	DWORD dwProcId;

	// number of results
	int nNumResults;

	// results list
	HWND phwResults[HWNDSEARCH_NUM];

} HWNDSEARCH, far* LPHWNDSEARCH;

// library function prototypes //

#define DECL_LIB_FN_PROTOTYPE(fn) WINDOWSANE_API FREObject fn (FREContext, void*, uint32_t, FREObject*)

WINDOWSANE_API void WindowsANEExtensionInitializer(void**, FREContextInitializer*, FREContextFinalizer*);
WINDOWSANE_API void WindowsANEContextInitializer(void*, const uint8_t*, FREContext, uint32_t*, const FRENamedFunction**);
WINDOWSANE_API void WindowsANEContextFinalizer(void*);

DECL_LIB_FN_PROTOTYPE(addFullScreenButton);
DECL_LIB_FN_PROTOTYPE(getDesktopBottom);
DECL_LIB_FN_PROTOTYPE(getDesktopLeft);
DECL_LIB_FN_PROTOTYPE(getDesktopRight);
DECL_LIB_FN_PROTOTYPE(getDesktopTop);
DECL_LIB_FN_PROTOTYPE(getLongestDisplaySide);
DECL_LIB_FN_PROTOTYPE(isFullScreen);
DECL_LIB_FN_PROTOTYPE(messageBox);
DECL_LIB_FN_PROTOTYPE(testANE);
DECL_LIB_FN_PROTOTYPE(toggleFullScreen);

// other function prototypes //

BOOL CALLBACK GetTopLevelHwndCallback(HWND, LPARAM);

HWND GetTopLevelHwnd(void);

#endif // WindowsANE_WindowsANE_h
