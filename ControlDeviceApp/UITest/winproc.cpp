#include "define.h"
#include <CommCtrl.h>
#include <sstream>

#if defined(UNICODE) || defined(_UNICODE)
#define tostringstream wostringstream
#else
#define tostringstream ostringstream
#endif

HWND hList = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_DESTROY) {
		if (hList) {
			::DestroyWindow(hList);
			hList = NULL;
		}

		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_KEYDOWN) {
		if (wParam == VK_ESCAPE) {
			//::DestroyWindow(hWnd);
			::SendMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);

			return 0;
		}
	}
	else if (uMsg == WM_CREATE) {
		// create List Control
		DWORD dwStyle = WS_CHILD | LVS_REPORT | LVS_EDITLABELS | WS_BORDER | LVS_OWNERDATA;
		hList = ::CreateWindowEx(0, WC_LISTVIEW, _T("Test List"), dwStyle,
			100, 100, 300, 400, hWnd, (HMENU)IDC_TESTLIST, (HINSTANCE)::GetModuleHandle(NULL), NULL);

		::ShowWindow(hList, SW_SHOW);
		::UpdateWindow(hList);

		LPTSTR szHeader[] = {_T("First"), _T("Second"), _T("Third")};
		LVCOLUMN lvc;
		::memset(&lvc, 0, sizeof(lvc));
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		for (int iCol = 0; iCol < 3; iCol++) {
			lvc.cx = 100;
			lvc.iSubItem = iCol;
			lvc.fmt = LVCFMT_CENTER;

			std::tostringstream oss;
			oss << _T("Col[") << iCol << _T("]");

			lvc.pszText = szHeader[iCol];

			ListView_InsertColumn(hList, iCol, &lvc);
		}

		LVITEM lvi;
		TCHAR buffer[100];
		::memset(&lvi, 0, sizeof(lvi));
		lvi.mask = LVIF_TEXT;
		for (int iRow = 0; iRow < 5; iRow++) {
			for (int iCol = 0; iCol < 3; iCol++) {
				lvi.iItem = iRow;
				lvi.iSubItem = iCol;

				std::tostringstream oss;
				oss << _T("Col[") << iCol << _T("] Row[") << iRow << _T("]");
				_stprintf_s(buffer, oss.str().c_str());

				lvi.pszText = buffer;
				lvi.cchTextMax = 100;

				int ret = 0;
				if (iCol == 0) {
					ret = ListView_InsertItem(hList, &lvi);
					if (ret == -1) {
						::MessageBox(NULL, oss.str().c_str(), _T("Error"), MB_OK);
					}
				}
				else {
					ret = ListView_SetItem(hList, &lvi);
					if (ret == FALSE) {
						::MessageBox(NULL, oss.str().c_str(), _T("Error"), MB_OK);
					}
				}

			}
		}

		return 0;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}