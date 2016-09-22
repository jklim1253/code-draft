#pragma once
#include <Windows.h>
#include <string>
#include <exception>
#include <sstream>

class INIHelperImpl;
class INIHelper {
public :
	INIHelper();
	INIHelper(const char* _filename);
	~INIHelper();

	INIHelper& useFile(const char* _filename) noexcept;
	INIHelper& useSection(const char* _section) noexcept;

	template<typename T>
	void SetValue(const char* szKey, const T& value) throw(...) {
		std::ostringstream oss;
		oss << value;

		Write(szKey, oss.str().c_str());
	}
	template<typename T>
	void SetValue(const char* szSection, const char* szKey, T value) throw(...) {
		useSection(szSection).SetValue(szKey, value);
	}
	template<typename T>
	void SetValue(const char* szFileName, const char* szSection, const char* szKey, T value) throw(...) {
		useFile(szFileName).SetValue(szSection, szKey, value);
	}
	template<typename T>
	T GetValue(const char* szKey, const T& default_value = T()) throw(...) {
		std::ostringstream oss;
		oss << default_value;
		std::string buffer = Read(szKey, oss.str().c_str());

		T ret;
		std::istringstream iss(buffer);
		iss >> ret;

		return ret;
	}
	template<>
	std::string GetValue(const char* szKey, const std::string& default_value) throw(...) {
		std::ostringstream oss;
		oss << default_value;
		std::string buffer = Read(szKey, oss.str().c_str());

		return buffer;
	}
	template<typename T>
	T GetValue(const char* szSection, const char* szKey, T default_value = T()) throw(...) {
		return useSection(szSection).SetValue(szKey, default_value);
	}
	template<typename T>
	T GetValue(const char* szFileName, const char* szSection, const char* szKey, T default_value = T()) throw(...) {
		return useFile(szFileName).SetValue(szSection, szKey, default_value);
	}
private :
	void Write(const char* szKey, const char* szValue) throw(...);
	std::string Read(const char* szKey, const char* szDefault) throw(...);

private :
	INIHelperImpl* impl;
};