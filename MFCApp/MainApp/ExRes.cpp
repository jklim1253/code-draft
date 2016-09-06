#include "stdafx.h"
#include "ExRes.h"

ExResource::ExResource()
	: hModule(NULL)
	, hBitmap(NULL)
{
}

ExResource::~ExResource()
{
	if (hBitmap) {
		::DeleteObject(hBitmap);
		hBitmap = NULL;
	}
	if (hModule) {
		::FreeLibrary(hModule);
		hModule = NULL;
	}
}

void ExResource::open(const TCHAR * dllname)
{
	hModule = ::LoadLibrary(dllname);
}

HBITMAP ExResource::getBitmap(UINT bitmapId)
{
	if (!hModule) {
		::AfxMessageBox(_T("dll do not loaded."));
	}

	hBitmap = (HBITMAP)::LoadImage(hModule, MAKEINTRESOURCE(bitmapId), IMAGE_BITMAP, 0, 0, LR_SHARED);

	return hBitmap;
}
