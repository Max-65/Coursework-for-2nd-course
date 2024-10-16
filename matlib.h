#pragma once

namespace matlib {
	class Array {
	private:
		int size_;
		double* arr;
	public:
		Array(int size = 0, double allocator = 0.0) : size_(size) {
			arr = new double[size_];
			for (int i = 0; i < size_; ++i) {
				arr[i] = allocator;
			}
		}
		~Array() {
			delete[] arr;
			arr = nullptr;
		}
		double& operator[](int const& i) const;
		int size() const;
		friend std::istream& operator>>(std::istream& is, Array& arr);
		friend std::ostream& operator<<(std::ostream& os, Array const& arr);
	};
/*
	vector x3:
	v.x
	v.y
	v.z
*/
	class vec3 {
	private:
		int size_;
	public:
		double x, y, z;
		vec3(double value = 0.0) : x(value), y(value), z(value), size_(3) {}
		vec3(double x, double y, double z) : x(x), y(y), z(z), size_(3) {}
		vec3(vec3 const& v) : x(v.x), y(v.y), z(v.z), size_(3) {}
		vec3& operator=(vec3 const& v);
		double& operator[](int const& i);
		double const& operator[](int const& i) const;
		vec3 operator+() const;
		vec3 operator-() const;
		vec3& operator+=(vec3 const& v);
		vec3& operator-=(vec3 const& v);
		int size() const;
		void reverse();
	};

/*
	matrix 3x3:
	a.x b.x c.x
	a.y b.y c.y
	a.z b.z c.z

	transposed matrix 3x3:
	a.x a.y a.z
	b.x b.y b.z
	c.x c.y c.z
	
	Note: transposed matrix is simpler to be sorted by column values - just by swapping vectors
*/
	class mat3 {
	private:
		vec3 a, b, c;
		int size_;
	public:
		mat3(double value = 0.0) : a(value, 0.0, 0.0), b(0.0, value, 0.0), c(0.0, 0.0, value), size_(3)	{}
		mat3(vec3 const& v1, vec3 const& v2, vec3 const& v3) : a(v1), b(v2), c(v3), size_(3) {}
		mat3(mat3 const& m) : a(m.a), b(m.b), c(m.c), size_(3) {}

		mat3& operator=(mat3 const& m);
		vec3& operator[](int const& i);
		vec3 const& operator[](int const& i) const;
		mat3 operator+() const;
		mat3 operator-() const;
		mat3& operator+=(mat3 const& m);
		mat3& operator-=(mat3 const& m);
		int size() const;
		void transpose();
		void reverse();
		void swapMaxEquation(vec3& v, int rang);
		friend std::ostream& operator<<(std::ostream& os, mat3 const& m);
	};

	double f(int const& i, double const& xi);
	vec3 operator*(vec3 const& vector, double value);
	void EvalCoef(Array const& x, Array const& y, mat3& A, vec3& b);
	void SolveSLAE(mat3& A, vec3& b, vec3& c);
	void Approx(vec3 const& c, Array const& x, Array& y);
	void ApproxQuality(Array const& y, Array const& y1, Array& d, double& max_d, int& max_d_i, double& approx_crit);
}
