#include <iostream>
#include "matlib.h"

// Array class
double& matlib::Array::operator[](int i) const {
	return arr[i];
}
int matlib::Array::size() const {
	return size_;
}

// Vector x3 class
matlib::vec3& matlib::vec3::operator=(vec3 const& v) {
	if (this != &v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
	return *this;
}
matlib::vec3 matlib::vec3::operator+() const {
	return vec3(x, y, z);
}
matlib::vec3 matlib::vec3::operator-() const {
	return vec3(-x, -y, -z);
}
matlib::vec3& matlib::vec3::operator+=(vec3 const& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
matlib::vec3& matlib::vec3::operator-=(vec3 const& v) {
	return *this += -v;
}
void matlib::vec3::reverse() {
	std::swap(x, z);
}

// Matrix 3x3 class
matlib::mat3& matlib::mat3::operator=(mat3 const& m) {
	if (this != &m) {
		a = m.a;
		b = m.b;
		c = m.c;
	}
	return *this;
}
matlib::mat3 matlib::mat3::operator+() const {
	mat3 m(a, b, c);
	return m;
}
matlib::mat3 matlib::mat3::operator-() const {
	mat3 m(-a, -b, -c);
	return m;
}
matlib::mat3& matlib::mat3::operator+=(mat3 const& m) {
	a += m.a;
	b += m.b;
	c += m.c;
	return *this;
}
matlib::mat3& matlib::mat3::operator-=(mat3 const& m) {
	*this += -m;
	return *this;
}
void matlib::mat3::transpose() {
	std::swap(a21, a12);
	std::swap(a31, a13);
	std::swap(a32, a23);
}
void matlib::mat3::reverse() {
	transpose();
	std::swap(a21, a32);
	std::swap(a11, a33);
	std::swap(a12, a23);
}
void matlib::mat3::sort(vec3& v, int rang) {
	transpose();
	if (rang == 3) {
		if (abs(b.x) > abs(a.x) && abs(b.x) > abs(c.x)) {
			std::swap(a, b);
			std::swap(v.x, v.y);
		}
		else if (abs(c.x) > abs(a.x) && abs(c.x) > abs(b.x)) {
			std::swap(a, c);
			std::swap(v.x, v.z);
		}
	}
	else if (rang == 2) {
		if (abs(c.y) > abs(b.y)) {
			std::swap(b, c);
			std::swap(v.y, v.z);
		}
	}
	transpose();
}

// Math library functions
double matlib::f1(double const& xi) {
	return 1;
}
double matlib::f2(double const& xi) {
	return xi;
}
double matlib::f3(double const& xi) {
	return std::exp(-xi);
}
matlib::vec3 matlib::operator*(vec3 const& vector, double value) {
	return vec3(vector.x * value, vector.y * value, vector.z * value);
}

std::istream& matlib::operator>>(std::istream& is, Array& arr) {
	for (int i = 0; i < arr.size(); ++i) {
		std::cin >> arr[i];
	}
	return is;
}
std::ostream& matlib::operator<<(std::ostream& os, Array const& arr) {
	for (int i = 0; i < arr.size(); ++i) {
		std::cout << arr[i] << ' ';
	}
	return os;
}
std::ostream& matlib::operator<<(std::ostream& os, mat3 const& m) {
	std::cout << m.a11 << ' ' << m.a12 << ' ' << m.a13 << '\n';
	std::cout << m.a21 << ' ' << m.a22 << ' ' << m.a23 << '\n';
	std::cout << m.a31 << ' ' << m.a32 << ' ' << m.a33;
	return os;
}
void matlib::EvalCoef(Array const& x, Array const& y, mat3& A, vec3& b) {
	for (int i = 0; i < x.size(); ++i) {
		A.a11 += f1(x[i]) * f1(x[i]);
		A.a12 += f1(x[i]) * f2(x[i]);
		A.a13 += f1(x[i]) * f3(x[i]);

		A.a21 += f2(x[i]) * f1(x[i]);
		A.a22 += f2(x[i]) * f2(x[i]);
		A.a23 += f2(x[i]) * f3(x[i]);

		A.a31 += f3(x[i]) * f1(x[i]);
		A.a32 += f3(x[i]) * f2(x[i]);
		A.a33 += f3(x[i]) * f3(x[i]);

		b.x += y[i];
		b.y += y[i] * x[i];
		b.z += y[i] * std::exp(-x[i]);
	}
}
void matlib::SolveSLAE(mat3& A, vec3& b, vec3& c) {
	int flag = 2;
	// flag == 2 -> Direct bypass
	// flag == 1 -> Reverse bypass
	// flag == 0 -> Break
	
	while (flag--) {
		if(flag) A.sort(b, 3);
		A.transpose();
		double q1(A.a12 / A.a11), q2(A.a13 / A.a11);
		vec3 v(A.a11, A.a21, A.a31);
		A -= mat3(0.0, v * q1, v * q2);
		b -= vec3(0.0, b.x * q1, b.x * q2);

		A.transpose();
		if(flag) A.sort(b, 2);
		A.transpose();

		v = vec3(A.a12, A.a22, A.a32);
		q1 = A.a23 / A.a22;
		A -= mat3(0.0, 0.0, v * q1);
		b -= vec3(0.0, 0.0, b.y * q1);

		A.transpose();
		A.reverse();
		b.reverse();
	}
	c = vec3(b.x / A.a11, b.y / A.a22, b.z / A.a33);
}
void matlib::Approx(vec3 const& c, Array const& x, Array& y) {
	for (int i = 0; i < x.size(); ++i) {
		y[i] = c.x + c.y * x[i] + c.z * std::exp(-x[i]);
	}
}
void matlib::ApproxQuality(Array const& y, Array const& y1, Array& d, double& max_d, int& max_d_i, double& approx_crit) {
	for (int i = 0; i < y.size(); ++i) {
		d[i] = abs(y[i] - y1[i]);

		if (d[i] > max_d) {
			max_d = d[i];
			max_d_i = i;
		}
		approx_crit += d[i] * d[i];
	}
}
