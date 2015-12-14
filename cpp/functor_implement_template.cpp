#include <iostream>
using namespace std;

int foo(int n) {
	return n + 1;
}
int bar(int n, int m) {
	return n + m;
}
void zoo(int n, const char* str) {
	while (n--)
		cout << "str : " << str << endl;
}

template<typename ReturnType, typename FunctionPointer, typename... Signature>
struct Function {
	FunctionPointer action;
	Function(const FunctionPointer& fp) : action(fp) {}
	ReturnType operator()(Signature... args) {
		return (*action)(args...);
	}
};

template<typename FunctionPointer, typename... Signature>
struct Function<void, FunctionPointer, Signature...> {
	FunctionPointer action;
	Function(const FunctionPointer& fp) : action(fp) {}
	void operator()(Signature... args) {
		(*action)(args...);
	}
};

template<typename ReturnType, typename Class, typename FunctionPointer, typename... Signature>
struct MemberFunction : public Function<ReturnType, FunctionPointer, Signature...> {
	MemberFunction(const FunctionPointer& fp) : Function(fp) {}
	ReturnType operator()(Class& obj, Signature... args) {
		return (obj.*action)(args...);
	}
};

class Tester {
private :
	int age;
public :
	void setAge(const int& a) { age = a; }
	int getAge() const { return age; }
};
int main() {

	Function<int, int(*)(int), int> ffoo(&foo);

	cout << ffoo(12) << endl;

	Function<int, int(*)(int, int), int, int> fbar(&bar);

	cout << fbar(12, 14) << endl;

	Function<void, void(*)(int, const char*), int, const char*> fzoo(&zoo);

	fzoo(3, "hello, world");

	Tester test;
	test.setAge(777);

	MemberFunction<int, Tester, int(Tester::*)() const> getAge(&Tester::getAge);

	cout << getAge(test) << endl;


	return 0;
}