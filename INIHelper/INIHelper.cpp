#include "INIHelper.hpp"

class INIHelperImpl {
public :
	std::string filename() const {
		return _filename;
	}
	void filename(const std::string& name) {
		// check name contain drive letter.
		std::string::size_type pos = name.find(":\\");
		if (pos == std::string::npos) {
			// set filename to current working directory and name.
			_filename = GetCurrentWorkingDirectory() + "\\" + name;
		}
	}
	std::string GetCurrentWorkingDirectory() const {
		DWORD allocSize = 16;
		char* buffer = new char[allocSize];
		DWORD dwSize;
		do {
			if (buffer) {
				delete[] buffer;
			}
			allocSize *= 2;
			buffer = new char[allocSize];

			dwSize = ::GetModuleFileNameA(NULL, buffer, allocSize);
		} while (dwSize >= allocSize);

		std::string cwd(buffer);
		delete[] buffer;

		std::string::size_type pos = cwd.find_last_of("\\");
		cwd = cwd.substr(0, pos);

		return cwd;
	}
	std::string section() const {
		return _section;
	}
	void section(const std::string& sect) {
		_section = sect;
	}
private :
	std::string _filename;
	std::string _section;
};
INIHelper::INIHelper()
	: impl(new INIHelperImpl)
{
}

INIHelper::INIHelper(const char * _filename)
	: impl(new INIHelperImpl)
{
	useFile(_filename);
}

INIHelper::~INIHelper()
{
	if (impl) {
		delete impl;
		impl = nullptr;
	}
}

INIHelper & INIHelper::useFile(const char * _filename) noexcept
{
	impl->filename(_filename);
	return *this;
}

INIHelper & INIHelper::useSection(const char * _section) noexcept
{
	impl->section(_section);
	return *this;
}
void INIHelper::Write(const char* szKey, const char* szValue) throw(...) {
	if (impl->filename().empty()) {
		throw std::exception("file did not set.");
	}
	if (impl->section().empty()) {
		throw std::exception("section did not set.");
	}
	BOOL ret = ::WritePrivateProfileStringA(impl->section().c_str(), szKey, szValue, impl->filename().c_str());
	if (ret == 0) {
		DWORD dwError = ::GetLastError();
		::MessageBoxA(NULL, "Error", "Error", MB_OK);
	}
}

std::string INIHelper::Read(const char * szKey, const char* szDefault) throw(...)
{
	DWORD allocSize = 16;
	DWORD dwSize;
	char* szReturn = nullptr;
	do {
		if (szReturn) {
			delete[] szReturn;
		}
		allocSize *= 2;
		szReturn = new char[allocSize];

		dwSize = ::GetPrivateProfileStringA(impl->section().c_str(), szKey, szDefault, szReturn, allocSize, impl->filename().c_str());
		if (dwSize == 0) {
			// not found key.
			return std::string("");
		}

	} while (dwSize == (allocSize - 1));

	std::string ret(szReturn);
	delete[] szReturn;

	return ret;
}