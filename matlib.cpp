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
matlib::vec3& matlib::vec3::operator+=(vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

// Matrix 3x3 class -----------------------------------------------------------
void matlib::mat3::transpose() {
	std::swap(a.y, b.x);
	std::swap(a.z, c.x);
	std::swap(b.z, c.y);
}
void matlib::mat3::sort(int rang) {
	if (rang == 3) {

	}
}
matlib::mat3& matlib::mat3::operator+=(mat3& m) {
	a += m.a;
	b += m.b;
	c += m.c;
	return *this;
}

// Math library functions -----------------------------------------------------
void matlib::EvalCoef(Array& x, Array& y, mat3& A, vec3& b) {
	vec3 v1, v2, v3;
	for (int i = 0; i < x.size(); ++i) {
		v1.x += 1;
		v2.x += x[i];
		v2.y += x[i] * x[i];
		v3.x += std::exp(-x[i]);
		v3.y += std::exp(-x[i]) * x[i];
		v3.z += std::exp(-x[i] * 2);

		b.x += y[i];
		b.y += y[i] * x[i];
		b.z += y[i] * std::exp(-x[i]);
	}
	mat3 tmp(v1, v2, v3);
	A += tmp;
}
void matlib::Solve_SLAE(mat3& A, vec3& b, vec3& c) {

}
