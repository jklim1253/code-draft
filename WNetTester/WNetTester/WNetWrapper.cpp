
#include "stdafx.h"
#include "WNetWrapper.h"
#include <winnetwk.h>



CString WNetWrapper::OpenBrowser(CWnd* pWnd)
{
	if (!pWnd) return CString();

	DWORD dwRet = ::WNetConnectionDialog(pWnd->GetSafeHwnd(), RESOURCETYPE_DISK);
	if (dwRet == NO_ERROR) {

	}
	else if (dwRet == ERROR_INVALID_PASSWORD) {

	}

	NETRESOURCE* netres = NULL;
	DWORD dwScope, dwType, dwUsage;
	HANDLE handle;

	dwScope = RESOURCE_CONNECTED;
	dwType = RESOURCETYPE_DISK;
	dwUsage = 0; // all resource.
	::WNetOpenEnum(dwScope, dwType, dwUsage, netres, &handle);



	return CString();
}
