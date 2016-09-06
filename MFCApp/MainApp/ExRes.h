#pragma once

class ExResource {
public :
	ExResource();
	~ExResource();

	void open(const TCHAR* dllname);

	HBITMAP getBitmap(UINT bitmapId);

private :
	HMODULE hModule;
	HBITMAP hBitmap;
};