#pragma once

#include <thread>

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
	Thread& operator=(Thread&& other) noexcept {
		if (t1.joinable()) {
			if (_force_quit)
				t1.detach();
			else
				t1.join();
		}
		t1 = std::move(other.t1);
		_force_quit = other._force_quit;
		return *this;
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

