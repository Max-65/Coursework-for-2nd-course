#include <iostream>
#include "matlib.h"

// Array class ----------------------------------------------------------------
double& matlib::Array::operator[](int i) const {
	return arr[i];
}
void matlib::Array::input() {
	for (int i = 0; i < size_; ++i) {
		std::cin >> arr[i];
	}
}
int matlib::Array::size() const {
	return size_;
}

// Vector x3 class ------------------------------------------------------------
matlib::vec3& matlib::vec3::operator+=(matlib::vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

// Matrix 3x3 class -----------------------------------------------------------
void matlib::mat3::transpose() {
	std::swap(a.y, b.x);
	std::swap(a.z, c.x);
	std::swap(b.z, c.y);
}
void matlib::mat3::sort() {

}
matlib::mat3& matlib::mat3::operator+=(matlib::mat3& m) {
	a += m.a;
	b += m.b;
	c += m.c;
}

// Math library functions -----------------------------------------------------
void matlib::EvalCoef(Array& x, Array& y, matlib::mat3& A, matlib::vec3& b) {
	for (int i = 0; i < x.size(); ++i) {

	}
}
