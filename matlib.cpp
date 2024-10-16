#include <iostream>
#include "matlib.h"

// Array class
double& matlib::Array::operator[](int const& i) const {
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
double& matlib::vec3::operator[](int const& i) {
	switch (i) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	exit(3);
}
double const& matlib::vec3::operator[](int const& i) const {
	switch (i) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	exit(3);
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
int matlib::vec3::size() const {
	return size_;
}
void matlib::vec3::reverse() {
	for (int i = 0; i < size() / 2; ++i) {
		std::swap((*this)[i], (*this)[size() - i - 1]);
	}
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
matlib::vec3& matlib::mat3::operator[](int const& i) {
	switch (i) {
	case 0:
		return a;
	case 1:
		return b;
	case 2:
		return c;
	}
	exit(3);
}
matlib::vec3 const& matlib::mat3::operator[](int const& i) const {
	switch (i) {
	case 0:
		return a;
	case 1:
		return b;
	case 2:
		return c;
	}
	exit(3);
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
int matlib::mat3::size() const {
	return size_;
}
void matlib::mat3::transpose() {
	for (int i = 0; i < size() - 1; ++i) {
		for (int j = i + 1; j < size(); ++j) {
			std::swap((*this)[i][j], (*this)[j][i]);
		}
	}
}
void matlib::mat3::reverse() {
	transpose();
	for (int i = 0; i < size() - 1; ++i) {
		for (int j = 0; j < size() - i - 1; ++j) {
			std::swap((*this)[i][j], (*this)[size() - j - 1][size() - i - 1]);
		}
	}
}
void matlib::mat3::swapMaxEquation(vec3& v, int rang) {
	transpose();
	int mx_i(size() - rang), beg_i(size() - rang);
	double mx(abs((*this)[beg_i][beg_i]));
	
	for (int i = beg_i + 1; i < size(); ++i) {
		if (abs((*this)[i][beg_i]) > mx) {
			mx = abs((*this)[i][beg_i]);
			mx_i = i;
		}
	}
	if (mx_i != beg_i) {
		std::swap((*this)[beg_i], (*this)[mx_i]);
		std::swap(v[beg_i], v[mx_i]);
	}
	transpose();
}

// Math library functions
double matlib::f(int const& i, double const& xi) {
	switch (i) {
	case 0:
		return 1;
	case 1:
		return xi;
	case 2:
		return std::exp(-xi);
	}
	exit(3);
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
	std::cout << m[0][0] << ' ' << m[1][0] << ' ' << m[2][0] << '\n';
	std::cout << m[0][1] << ' ' << m[1][1] << ' ' << m[2][1] << '\n';
	std::cout << m[0][2] << ' ' << m[1][2] << ' ' << m[2][2];
	return os;
}
void matlib::EvalCoef(Array const& x, Array const& y, mat3& A, vec3& b) {
	for (int i = 0; i < x.size(); ++i) {
		for (int k = 0; k < A.size(); ++k) {
			for (int l = 0; l < A.size(); ++l) {
				A[k][l] += f(k, x[i]) * f(l, x[i]);
			}
			b[k] += y[i] * f(k, x[i]);
		}
	}
}
void matlib::SolveSLAE(mat3& A, vec3& b, vec3& c) {
	int flag(2), mx_i(0);
	Array q(A.size() - 1);
	vec3 v;
	// flag == 2 -> Direct bypass
	// flag == 1 -> Reverse bypass
	// flag == 0 -> Break
	
	while (flag--) {
		for (int r = A.size(); r > 1; --r) {
			mx_i = A.size() - r;
			if (flag) A.swapMaxEquation(b, r);

			for (int i = 0; i < A.size() - 1; ++i) {
				q[i] = A[mx_i][i + 1] / A[mx_i][mx_i];
			}

			A.transpose();
			v = A[mx_i];
			for (int i = mx_i + 1; i < A.size(); ++i) {
				A[i] -= v * q[i - 1];
				b[i] -= b[mx_i] * q[i - 1];
			}
			A.transpose();
		}
		A.reverse();
		b.reverse();
	}
	for (int i = 0; i < A.size(); ++i) {
		c[i] = b[i] / A[i][i];
	}
}
void matlib::Approx(vec3 const& c, Array const& x, Array& y) {
	for (int i = 0; i < x.size(); ++i) {
		for (int k = 0; k < c.size(); ++k) {
			y[i] += c[k] * f(k, x[i]);
		}
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
