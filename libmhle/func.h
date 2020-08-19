#pragma once
namespace mhle {
	static int gcd(const int& a, const int& b) {
		return b ? gcd(b, a % b) : a;
	}
	static int lcm(const int& a, const int& b) {
		return a * b / gcd(a, b);
	}
}