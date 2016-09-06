#include "stdafx.h"
#include "WICWrapper.h"

WICWrapper::WICWrapper()
	: pFactory(NULL)
{
	::CoInitialize(NULL);

	HRESULT hr = ::CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFactory));
}

WICWrapper::~WICWrapper()
{
}
