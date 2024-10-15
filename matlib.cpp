#include <iostream>
#include "matlib.h"

// Array class
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

void matlib::mat3::print() const {
	std::cout << '\n' << a11 << ' ' << a12 << ' ' << a13 << '\n';
	std::cout << a21 << ' ' << a22 << ' ' << a23 << '\n';
	std::cout << a31 << ' ' << a32 << ' ' << a33 << '\n';
}
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

// Math library functions
matlib::vec3 matlib::operator*(vec3 const& vector, double value) {
	return vec3(vector.x * value, vector.y * value, vector.z * value);
}
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
	v1.y = v2.x;
	v1.z = v3.x;
	v2.z = v3.y;

	A = mat3(v1, v2, v3);
}
void matlib::mat3::sort(vec3& v, int rang) {
	transpose();
	if (rang == 3) {
		if (b.x > a.x && b.x > c.x) {
			std::swap(a, b);
			std::swap(v.x, v.y);
		}
		else if (c.x > a.x && c.x > b.x) {
			std::swap(a, c);
			std::swap(v.x, v.z);
		}
	}
	else if (rang == 2) {
		if (c.y > b.y) {
			std::swap(b, c);
			std::swap(v.y, v.z);
		}
	}
	else if (rang == 1) {
		if (b.x != 0) {
			std::swap(a, b);
			std::swap(v.x, v.y);
		}
		else if (c.x != 0) {
			std::swap(a, c);
			std::swap(v.x, v.z);
		}
		else if (c.y != 0) {
			std::swap(b, c);
			std::swap(v.y, v.z);
		}
	}
	transpose();
}
void matlib::Solve_SLAE(mat3& A, vec3& b, vec3& c) {
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
