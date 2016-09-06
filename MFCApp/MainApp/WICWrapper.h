#pragma once

#pragma comment(lib, "windowscodecs.lib")

#include <wincodec.h>
#include <wincodecsdk.h>

class WICWrapper {
public :
	WICWrapper();
	~WICWrapper();

private :
	IWICImagingFactory* pFactory;
};