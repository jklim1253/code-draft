#include "define.h"
#include <CommCtrl.h>	// for LISTVIEW control
#include <sstream>

#if defined(UNICODE) || defined(_UNICODE)
#define tostringstream wostringstream
#else
#define tostringstream ostringstream
#endif

IDGenerator::Control_ID_Type IDGenerator::operator () () {
	static Control_ID_Type cid = 100;
	return cid++;
}

HWND hPrevFocusWnd = NULL;
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
			if (hPrevFocusWnd) {
				::SetFocus(hPrevFocusWnd);
			}

			::SendMessage(hMainWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
			return 0;
		}
	}
	else if (uMsg == WM_LBUTTONDOWN) {
		hPrevFocusWnd = ::GetParent(hWnd);
		::SetFocus(hWnd);

		return 0;
	}
	else if (uMsg == WM_CREATE) {
		// create List Control
		DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_TABSTOP | LVS_REPORT;
		hList = ::CreateWindowEx(dwExStyle, WC_LISTVIEW, _T("Test List"), dwStyle,
			100, 100, 300, 400, hWnd, (HMENU)IDGen, (HINSTANCE)::GetModuleHandle(NULL), NULL);

		//::ShowWindow(hList, SW_SHOW);
		//::UpdateWindow(hList);

		LPTSTR szHeader[] = {_T("First"), _T("Second"), _T("Third")};
		LVCOLUMN lvc;
		::memset(&lvc, 0, sizeof(lvc));
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		for (int iCol = 0; iCol < 3; iCol++) {
			lvc.cx = 90;
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