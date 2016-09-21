#pragma once

#include <string>

class IDevice {
public :
	virtual bool initialize() = 0;
	virtual bool release() = 0;
	virtual std::string name() const = 0;
};
class DeviceBase : public IDevice {
public :
	virtual bool initialize() {}
	virtual bool release() {}
	virtual std::string name() const {
		return std::string("unknown-device");
	}
};

class Camera : public DeviceBase {
public :
	virtual std::string name() const {
		return std::string("default - camera");
	}
};

class DIOBoard : public DeviceBase {
public :
	virtual std::string name() const {
		return std::string("default - DIO board");
	}
};

class BarcodeReader : public DeviceBase {
public :
	virtual std::string name() const {
		return std::string("default - barcode reader");
	}
};

class ServoMotor : public DeviceBase {
public :
	virtual std::string name() const {
		return std::string("default - servo motor");
	}
};