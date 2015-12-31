#pragma once

#include <iostream>
#include <string>
using namespace std;

class Number {
private:
	string value;
public:
	Number(const string& v) : value(v.rbegin(), v.rend()) {}
	template<typename InputIter>
	Number(InputIter Last, InputIter First) : value(Last, First) {}
	template<typename Integer>
	Number(const Integer& i) {
		if (i == 0) {
			value.push_back('0');
			return;
		}

		Integer v = i;
		while (v > 0) {
			value.push_back('0' + v % 10);
			v = v / 10;
		}
	}
	friend Number operator + (const Number& lhs, const Number& rhs) {
		string result;
		int tmp = 0, upper = 0;
		auto lit = lhs.value.cbegin();
		auto rit = rhs.value.cbegin();
		while (lit != lhs.value.cend() || rit != rhs.value.cend() || upper != 0) {
			tmp = upper;
			if (lit != lhs.value.cend()) {
				tmp += *lit - '0';
				++lit;
			}
			if (rit != rhs.value.cend()) {
				tmp += *rit - '0';
				++rit;
			}
			result.push_back(tmp % 10 + '0');
			upper = tmp / 10;
		}

		return Number(result.begin(), result.end());
	}
	friend bool operator == (const Number& lhs, const Number& rhs) {
		if (lhs.value.size() != rhs.value.size())
			return false;

		auto lit = lhs.value.cbegin();
		auto rit = rhs.value.cbegin();
		while (lit != lhs.value.cend() && *lit++ == *rit++);

		return (lit == lhs.value.cend());
	}
	friend bool operator != (const Number& lhs, const Number& rhs) {
		return !(lhs == rhs);
	}
	Number& operator ++ () {
		*this = *this + Number(1);
		return *this;
	}
	friend ostream& operator << (ostream& os, const Number& o) {
		auto it = o.value.crbegin();
		while (it != o.value.crend()) {
			os << *it++;
		}
		return os;
	}
};
