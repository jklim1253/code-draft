#pragma once

#include <Windows.h>
#include <tchar.h>

enum ids_control {
	IDC_TESTLIST = 100,
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);