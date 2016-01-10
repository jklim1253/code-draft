#include "ThreadManager.h"
#include <iostream>
#include <string>
#include <mutex>
using namespace std;

std::mutex mu;

template<typename First, typename... Args>
void shared_print(First first, Args... args) {
	std::lock_guard<mutex> locker(mu);
	_print(first, args...);
}
template<typename First, typename... Args>
void _print(First first, Args... args) {
	std::cout << first;
	_print(args...);
}
void _print() {
	std::cout << endl;
}

void function_1() {
	cout << "Beauty is only skin-deep" << endl;
}

class Functor {
public :
	void operator()(const string& msg) {
		for (int i = 0; i > -50; --i) {
			shared_print("from t1 : ", i, " : ", msg);
		}
		shared_print("work done.");
	}
};

//template<typename Fn, typename... Args>
//struct Task {
//	Fn fn;
//	Args args;
//};
//
//template<typename Fn, typename... Args>
//Task<Fn, Args...> make_task(Fn&& fn, Args&&...args) {
//	return Task<Fn, Args...>(fn, args...);
//}

int main() {
	string s = "Where there is no trust, there is no love";
	Thread some;// ((Functor()), std::string("test"));
	Thread&& job = Thread((Functor()), s);
	some = std::move(job);
	shared_print("t1 is ", some.get_id());

	some.force_quit(false);

	for (int i = 0; i < 100; ++i) {
		shared_print("from main : ", i);
	}

	Thread t2 = std::move(some);

	shared_print("t1 is ", some.get_id());
	shared_print("t2 is ", t2.get_id());

	return 0;
}