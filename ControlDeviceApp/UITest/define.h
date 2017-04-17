#pragma once

#include <Windows.h>
#include <tchar.h>
#include "singleton.hpp"

struct IDGenerator : public singleton<IDGenerator> {
	typedef UINT Control_ID_Type;
	Control_ID_Type operator () ();
};

#define IDGen (IDGenerator::Reference()())

extern HWND hMainWnd;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);