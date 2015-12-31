#include "big_number.h"
#include <iostream>
#include <chrono>
using namespace std;

template<typename Function, typename... Args>
chrono::duration<double, milli> check_duration(Function func, Args... args) {
	chrono::steady_clock::time_point tick = chrono::steady_clock::now();

	func(args...);

	chrono::steady_clock::duration elapsed = chrono::steady_clock::now() - tick;

	return chrono::duration_cast<chrono::duration<double, milli>>(elapsed);
}
int main(int argc, char* argv[]) {

	chrono::duration<double, milli> elapsed =
		check_duration([]() {
		Number a(0);

		while (a != 10000) {

			cout << a << endl;

			++a;
		}
	});

	cout << "elapsed time : " << elapsed.count() << " sec" << endl;

	return 0;
}