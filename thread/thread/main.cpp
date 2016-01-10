#include <iostream>
#include <thread>
#include <string>
using namespace std;

void function_1() {
	cout << "Beauty is only skin-deep" << endl;
}

class Functor {
public :
	void operator()() {
		for (int i = 0; i > -50; --i) {
			cout << "from t1 : " << i << endl;
		}
	}
};

class Thread {
private :
	std::thread t1;
	bool _force_quit;
public :
	template<typename Fn, typename... Args>
	Thread(Fn&& fn, Args&&... args) : t1(fn, args...), _force_quit(true) {
	}
	Thread() : _force_quit(true) {
	}
	Thread(Thread&& other) : t1(std::move(other.t1)), _force_quit(other._force_quit) {
	}
	Thread(const Thread&) = delete;
	Thread& operator=(const Thread&) = delete;
	~Thread() {
		if (t1.joinable()) {
			if (_force_quit)
				t1.detach();
			else
				t1.join();
		}
	}

	void force_quit(bool quit) {
		_force_quit = quit;
	}
	std::thread::id get_id() const noexcept {
		return t1.get_id();
	}
};

int main() {
	Thread t1((Functor()));
	cout << "t1 is " << t1.get_id() << endl;

	//t1.force_quit(false);

	for (int i = 0; i < 100; ++i) {
		cout << "from main : " << i << endl;
	}

	Thread t2 = std::move(t1);

	cout << "t1 is " << t1.get_id() << endl;
	cout << "t2 is " << t2.get_id() << endl;

	return 0;
}