//
//  WindowsANE.cpp
//

// primary include //

#include "WindowsANE.h"

// system includes //

#include <stdlib.h>

// globals //

// function list
FRENamedFunction* g_pFunc = NULL;

// fullscreen flag
bool g_bIsFullScreen = FALSE;

// stored window styles
DWORD g_dwStyle   = NULL;
DWORD g_dwStyleEx = NULL;

// functions required by Flash //

// extension initializer
WINDOWSANE_API void WindowsANEExtensionInitializer(void**                 ppExtDataToSet,
												   FREContextInitializer* pCtxInitializerToSet,
												   FREContextFinalizer*   pCtxFinalizerToSet)
{
	// reset data
	(*ppExtDataToSet) = NULL;

	// set context initializer
	(*pCtxInitializerToSet) = &WindowsANEContextInitializer;

	// reset finalizer
	(*pCtxFinalizerToSet) = &WindowsANEContextFinalizer;
}

// context initializer
WINDOWSANE_API void WindowsANEContextInitializer(void*                    pExtData,
												 const uint8_t*           pCtxType,
												 FREContext               ctx,
												 uint32_t*                pNumFunctionsToSet,
												 const FRENamedFunction** pFunctionsToSet)
{
	// set number of functions
	(*pNumFunctionsToSet) = 10;
	
	// allocate memory for functions
	g_pFunc = g_pFunc ? g_pFunc : (FRENamedFunction*) malloc(sizeof(FRENamedFunction) * (*pNumFunctionsToSet));
	
	// add functions
	#define SET_LIB_FN_POINTER(n, str, fn) g_pFunc[n].name = (const uint8_t*) str; g_pFunc[n].functionData = NULL; g_pFunc[n].function = &fn
	
	SET_LIB_FN_POINTER(0, "addFullScreenButton",   addFullScreenButton);
	SET_LIB_FN_POINTER(1, "getDesktopBottom",      getDesktopBottom);
	SET_LIB_FN_POINTER(2, "getDesktopLeft",        getDesktopLeft);
	SET_LIB_FN_POINTER(3, "getDesktopRight",       getDesktopRight);
	SET_LIB_FN_POINTER(4, "getDesktopTop",         getDesktopTop);
	SET_LIB_FN_POINTER(5, "getLongestDisplaySide", getLongestDisplaySide);
	SET_LIB_FN_POINTER(6, "isFullScreen",          isFullScreen);
	SET_LIB_FN_POINTER(7, "messageBox",            messageBox);
	SET_LIB_FN_POINTER(8, "testANE",               testANE);
	SET_LIB_FN_POINTER(9, "toggleFullScreen",      toggleFullScreen);
	
	// set function pointer
	(*pFunctionsToSet) = g_pFunc;
}

// context finalizer
WINDOWSANE_API void WindowsANEContextFinalizer(void* pExtData)
{
	// free function list
	SAFE_FREE(g_pFunc);
}

// library function implementations //

// addFullScreenButton() -- add button to title bar
WINDOWSANE_API FREObject addFullScreenButton(FREContext ctx,
											 void*      pFuncData,
											 uint32_t   argc,
											 FREObject  argv[])
{
	// not used
	// will not be releasing any windows desktop apps
	// will be waiting for Adobe to support Windows Phone :/

	// ok
	return(NULL);
}

// getDesktopBottom() -- retrieve bottom of desktop
WINDOWSANE_API FREObject getDesktopBottom(FREContext ctx,
										  void*      pFuncData,
										  uint32_t   argc,
										  FREObject  argv[])
{
	// passed parameters
	int32_t nWindowX = 0;
	int32_t nWindowY = 0;
	int32_t nWindowW = 0;
	int32_t nWindowH = 0;

	// get parameters
	FREGetObjectAsInt32(argv[0], &nWindowX);
	FREGetObjectAsInt32(argv[1], &nWindowY);
	FREGetObjectAsInt32(argv[2], &nWindowW);
	FREGetObjectAsInt32(argv[3], &nWindowH);

	// reset return value
	int nRet = 0;

	// window rectangle
	RECT rWnd;

	// set window rectangle
	rWnd.left   = nWindowX;
	rWnd.right  = nWindowX + nWindowW;
	rWnd.top    = nWindowY;
	rWnd.bottom = nWindowY + nWindowH;
		
	// get intersecting monitor
	HMONITOR hMonitor = MonitorFromRect(&rWnd, MONITOR_DEFAULTTONEAREST);

	// check monitor
	if(hMonitor)
	{
		// monitor info
		MONITORINFO mi;

		// prepare structure
		mi.cbSize = sizeof(mi);

		// get monitor info
		if(GetMonitorInfo(hMonitor, &mi))
		{
			// set requested value
			nRet = mi.rcWork.bottom;
		}
	}

	// object to return
	FREObject pRet = NULL;

	// create object
	FRENewObjectFromInt32(nRet, &pRet);

	// send it
	return(pRet);
}

// getDesktopLeft() -- retrieve left side of desktop
WINDOWSANE_API FREObject getDesktopLeft(FREContext ctx,
										void*      pFuncData,
										uint32_t   argc,
										FREObject  argv[])
{
	// passed parameters
	int32_t nWindowX = 0;
	int32_t nWindowY = 0;
	int32_t nWindowW = 0;
	int32_t nWindowH = 0;

	// get parameters
	FREGetObjectAsInt32(argv[0], &nWindowX);
	FREGetObjectAsInt32(argv[1], &nWindowY);
	FREGetObjectAsInt32(argv[2], &nWindowW);
	FREGetObjectAsInt32(argv[3], &nWindowH);

	// reset return value
	int nRet = 0;

	// window rectangle
	RECT rWnd;

	// set window rectangle
	rWnd.left   = nWindowX;
	rWnd.right  = nWindowX + nWindowW;
	rWnd.top    = nWindowY;
	rWnd.bottom = nWindowY + nWindowH;
		
	// get intersecting monitor
	HMONITOR hMonitor = MonitorFromRect(&rWnd, MONITOR_DEFAULTTONEAREST);

	// check monitor
	if(hMonitor)
	{
		// momitor info
		MONITORINFO mi;

		// prepare structure
		mi.cbSize = sizeof(mi);

		// get monitor info
		if(GetMonitorInfo(hMonitor, &mi))
		{
			// set requested value
			nRet = mi.rcWork.left;
		}
	}

	// object to return
	FREObject pRet = NULL;

	// create object
	FRENewObjectFromInt32(nRet, &pRet);

	// send it
	return(pRet);
}

// getDesktopRight() -- retrieve right side of desktop
WINDOWSANE_API FREObject getDesktopRight(FREContext ctx,
										 void*      pFuncData,
										 uint32_t   argc,
										 FREObject  argv[])
{
	// passed parameters
	int32_t nWindowX = 0;
	int32_t nWindowY = 0;
	int32_t nWindowW = 0;
	int32_t nWindowH = 0;

	// get parameters
	FREGetObjectAsInt32(argv[0], &nWindowX);
	FREGetObjectAsInt32(argv[1], &nWindowY);
	FREGetObjectAsInt32(argv[2], &nWindowW);
	FREGetObjectAsInt32(argv[3], &nWindowH);

	// reset return value
	int nRet = 0;

	// window rectangle
	RECT rWnd;

	// set window rectangle
	rWnd.left   = nWindowX;
	rWnd.right  = nWindowX + nWindowW;
	rWnd.top    = nWindowY;
	rWnd.bottom = nWindowY + nWindowH;
		
	// get intersecting monitor
	HMONITOR hMonitor = MonitorFromRect(&rWnd, MONITOR_DEFAULTTONEAREST);

	// check monitor
	if(hMonitor)
	{
		// momitor info
		MONITORINFO mi;

		// prepare structure
		mi.cbSize = sizeof(mi);

		// get monitor info
		if(GetMonitorInfo(hMonitor, &mi))
		{
			// set requested value
			nRet = mi.rcWork.right;
		}
	}

	// object to return
	FREObject pRet = NULL;

	// create object
	FRENewObjectFromInt32(nRet, &pRet);

	// send it
	return(pRet);
}

// getDesktopTop() -- retrieve top of desktop
WINDOWSANE_API FREObject getDesktopTop(FREContext ctx,
									   void*      pFuncData,
									   uint32_t   argc,
									   FREObject  argv[])
{
	// passed parameters
	int32_t nWindowX = 0;
	int32_t nWindowY = 0;
	int32_t nWindowW = 0;
	int32_t nWindowH = 0;

	// get parameters
	FREGetObjectAsInt32(argv[0], &nWindowX);
	FREGetObjectAsInt32(argv[1], &nWindowY);
	FREGetObjectAsInt32(argv[2], &nWindowW);
	FREGetObjectAsInt32(argv[3], &nWindowH);

	// reset return value
	int nRet = 0;

	// window rectangle
	RECT rWnd;

	// set window rectangle
	rWnd.left   = nWindowX;
	rWnd.right  = nWindowX + nWindowW;
	rWnd.top    = nWindowY;
	rWnd.bottom = nWindowY + nWindowH;
		
	// get intersecting monitor
	HMONITOR hMonitor = MonitorFromRect(&rWnd, MONITOR_DEFAULTTONEAREST);

	// check monitor
	if(hMonitor)
	{
		// momitor info
		MONITORINFO mi;

		// prepare structure
		mi.cbSize = sizeof(mi);

		// get monitor info
		if(GetMonitorInfo(hMonitor, &mi))
		{
			// set requested value
			nRet = mi.rcWork.top;
		}
	}

	// object to return
	FREObject pRet = NULL;

	// create object
	FRENewObjectFromInt32(nRet, &pRet);

	// send it
	return(pRet);
}

// getLongestDisplaySide() -- retrieve maximum value for resolution
FREObject getLongestDisplaySide(FREContext ctx,
								void*      pFuncData,
								uint32_t   argc,
								FREObject  argv[])
{
	// reset return value
	int nRet = 0;

	// get shell window
	HWND hWnd = GetShellWindow();

	// if failed, try desktop window
	if(!hWnd)
		hWnd = GetDesktopWindow();

	// check window
	if(hWnd)
	{
		// window rect
		RECT rWnd;

		// get window rect
		if(GetWindowRect(hWnd, &rWnd))
		{
			// compute sides
			int nSideX = rWnd.right  - rWnd.left;
			int nSideY = rWnd.bottom - rWnd.top;

			// get longest side
			nRet = (nSideX > nSideY) ? nSideX : nSideY;
		}
	}
	
	// object to return
	FREObject pRet = NULL;
	
	// create object
	FRENewObjectFromInt32(nRet, &pRet);
	
	// send it
	return(pRet);
}

// isFullScreen() -- retrieve full-screen flag
WINDOWSANE_API FREObject isFullScreen(FREContext ctx,
									  void*      pFuncData,
									  uint32_t   argc,
									  FREObject  argv[])
{
	// object to return
	FREObject pRet = NULL;

	// create object
	FRENewObjectFromInt32((int32_t) (g_bIsFullScreen ? 1 : 0), &pRet);

	// ok
	return(pRet);
}

// messageBox() -- display simple modal alert box
WINDOWSANE_API FREObject messageBox(FREContext ctx,
									void*      pFuncData,
									uint32_t   argc,
									FREObject  argv[])
{
	// text lengths
	uint32_t nCaptionLen;
	uint32_t nMessageLen;

	// text data
	const uint8_t* pCaption;
	const uint8_t* pMessage;

	// get objects
	FREGetObjectAsUTF8(argv[0], &nCaptionLen, &pCaption);
	FREGetObjectAsUTF8(argv[1], &nMessageLen, &pMessage);

	// compute buffer sizes
	int nCaptionBufSz = sizeof(wchar_t) * (nCaptionLen + 1);
	int nMessageBufSz = sizeof(wchar_t) * (nMessageLen + 1);

	// allocate wide strings
	wchar_t* pCaptionW = nCaptionLen ? (wchar_t*) malloc(nCaptionBufSz) : NULL;
	wchar_t* pMessageW = nMessageLen ? (wchar_t*) malloc(nMessageBufSz) : NULL;

	// convert strings
	if(pCaptionW) MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (const char*) pCaption, -1, pCaptionW, nCaptionBufSz);
	if(pMessageW) MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (const char*) pMessage, -1, pMessageW, nMessageBufSz);

	// get window handle
	HWND hWnd = GetTopLevelHwnd();

	// set message box flags
	DWORD dwFlags = MB_ICONEXCLAMATION | MB_OK | MB_SETFOREGROUND;

	// add modal flag
	dwFlags |= hWnd ? MB_APPLMODAL : MB_TASKMODAL;

	// display message box	
	MessageBox(hWnd, pMessageW, pCaptionW, dwFlags);

	// release wide strings
	SAFE_FREE(pCaptionW);
	SAFE_FREE(pMessageW);

	// ok
	return(NULL);
}

// testANE() -- verify that the library is working correctly
WINDOWSANE_API FREObject testANE(FREContext ctx,
								 void*      pFuncData,
								 uint32_t   argc,
								 FREObject  argv[])
{
	// passed parameter
	int32_t nData = 0;

	// get passed parameter
	FREGetObjectAsInt32(argv[0], &nData);

	// object to return
	FREObject pRet = NULL;

	// create object
	FRENewObjectFromInt32(nData, &pRet);

	// ok (errors will fall thru)
	return(pRet);
}

// toggleFullScreen() -- toggle full-screen mode
WINDOWSANE_API FREObject toggleFullScreen(FREContext ctx,
										  void*      pFuncData,
										  uint32_t   argc,
										  FREObject  argv[])
{
	// passed parameters
	int32_t nWindowX = 0;
	int32_t nWindowY = 0;
	int32_t nWindowW = 0;
	int32_t nWindowH = 0;

	// get parameters
	FREGetObjectAsInt32(argv[0], &nWindowX);
	FREGetObjectAsInt32(argv[1], &nWindowY);
	FREGetObjectAsInt32(argv[2], &nWindowW);
	FREGetObjectAsInt32(argv[3], &nWindowH);

	// get window handle
	HWND hWnd = GetTopLevelHwnd();

	// check window
	if(!hWnd)
		return(NULL);

	// get monitor
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// monitor info
	MONITORINFO mi;

	// prepare monitor info
	mi.cbSize = sizeof(mi);

	// get monitor info
	if(!GetMonitorInfo(hMonitor, &mi))
		return(NULL);

	// check fullscreen flag
	if(g_bIsFullScreen)
	{
		// restore window style
		SetWindowLong(hWnd, GWL_STYLE,   g_dwStyle);
		SetWindowLong(hWnd, GWL_EXSTYLE, g_dwStyleEx);

		// restore window size/position
		MoveWindow(hWnd,
				   nWindowX,
				   nWindowY,
				   nWindowW,
				   nWindowH,
				   TRUE);

		// clear flag
		g_bIsFullScreen = FALSE;
	}
	else
	{
		// set flag
		g_bIsFullScreen = TRUE;

		// save window style
		g_dwStyle   = (DWORD) GetWindowLong(hWnd, GWL_STYLE);
		g_dwStyleEx = (DWORD) GetWindowLong(hWnd, GWL_EXSTYLE);

		// set new window style
		SetWindowLong(hWnd,
					  GWL_STYLE,
					  WS_POPUP | WS_VISIBLE);
		
		// set new extended window style
		SetWindowLong(hWnd,
					  GWL_EXSTYLE,
					  WS_EX_TOPMOST);
		
		// expand window rect
		MoveWindow(hWnd,
				   mi.rcMonitor.left,
				   mi.rcMonitor.top,
				   mi.rcMonitor.right  - mi.rcMonitor.left,
				   mi.rcMonitor.bottom - mi.rcMonitor.top,
				   TRUE);
	}

	// ok
	return(NULL);
}

// other function implementations //

// GetTopLevelHwnd() -- get handle to main application window
HWND GetTopLevelHwnd(void)
{
	// return value
	HWND hWnd = NULL;

	// search results
	HWNDSEARCH hws;

	// init search results
	ZeroMemory(&hws, sizeof(HWNDSEARCH));

	// set process id
	hws.dwProcId = GetCurrentProcessId();

	// search for window
	EnumWindows(&GetTopLevelHwndCallback, (LPARAM) &hws);

	// check results
	if(hws.nNumResults)
	{
		// process each
		for(int c1 = 0; c1 < hws.nNumResults; c1++)
		{
			// get current window handle
			HWND hwCurrent = hws.phwResults[c1];

			// check visibility
			if(IsWindowVisible(hwCurrent))
			{
				// get parent window handle
				HWND hwParent = GetParent(hwCurrent);

				// set pass flag
				BOOL bPass = TRUE;

				// compare with found windows (if parent is in list, this is not top-level)
				for(int c2 = 0; c2 < hws.nNumResults; c2++)
					if(c1 != c2)
						if(hwParent == hws.phwResults[c2])
							bPass = FALSE;

				// check for success
				if(bPass)
					hWnd = hwCurrent;
			}
		}
	}

	// ok
	return(hWnd);
}

// GetTopLevelHwndCallback() -- callback for window search procedure
BOOL CALLBACK GetTopLevelHwndCallback(HWND   hWnd,
									  LPARAM lParam)
{
	// current window process id
	DWORD dwWndProcId = NULL;

	// get window process id
	GetWindowThreadProcessId(hWnd, &dwWndProcId);

	// retrieve search results
	LPHWNDSEARCH pHWS = (LPHWNDSEARCH) lParam;

	// compare processes
	if(pHWS->dwProcId == dwWndProcId)
	{
		// store it
		pHWS->phwResults[pHWS->nNumResults++] = hWnd;

		// check for overflow
		if(pHWS->nNumResults >= HWNDSEARCH_NUM)
			return(FALSE);
	}

	// keep going
	return(TRUE);
}

// eof //
