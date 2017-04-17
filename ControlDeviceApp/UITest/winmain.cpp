#include "define.h"

HWND hMainWnd;

INT WINAPI _tWinMain(HINSTANCE hInst,
	HINSTANCE hPreInst,
	LPTSTR lpCmdLine,
	INT nCmdShow) {

	LPCTSTR lpszClassName = _T("UITest Application Class");

	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hInstance = hInst;
	wcex.lpfnWndProc = &WndProc;
	wcex.lpszClassName = lpszClassName;
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	if (!::RegisterClassEx(&wcex)) {
		DWORD dwError = ::GetLastError();
		return dwError;
	}

	DWORD dwStyle = WS_POPUP | WS_VISIBLE | WS_TABSTOP;

	INT cx = 800;
	INT cy = 600;
	INT x = (::GetSystemMetrics(SM_CXSCREEN) - cx) / 2;
	INT y = (::GetSystemMetrics(SM_CYSCREEN) - cy) / 2;

	hMainWnd = ::CreateWindowEx(0, lpszClassName, _T("UI Test"), dwStyle, x, y, cx, cy, NULL, NULL, hInst, NULL);
	if (hMainWnd == NULL) {
		DWORD dwError = ::GetLastError();
		return dwError;
	}

	::ShowWindow(hMainWnd, SW_NORMAL);
	::UpdateWindow(hMainWnd);

	MSG msg;
	while (true) {
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			break;
		}
	}

	return INT(msg.wParam);
}