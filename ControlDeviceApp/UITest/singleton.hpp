#pragma once

template<typename Class>
class singleton {
protected :
	singleton() {}
	~singleton() {}
public :
	static Class& Reference() {
		static Class inst;
		return inst;
	}
};