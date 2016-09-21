#pragma once
#pragma comment(lib, "mpr.lib")
#include <afxwin.h>

class WNetWrapper {
public :
	CString OpenBrowser(CWnd* pWnd);
};