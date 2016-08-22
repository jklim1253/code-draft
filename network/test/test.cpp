#include <iostream>

struct Test {
	int a;

	int& A() {
		return a;
	}
};

int main() {
	Test test;

	test.A() = 3;

	std::cout << test.A() << std::endl;

	return 0;
}