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
		double& operator[](int i) const;
		void input();
		int size() const;
	};
/*
	vector x3:
	v.x
	v.y
	v.z
*/
	class vec3 {
	public:
		double x, y, z;
		vec3(double value = 0.0) : x(value), y(value), z(value) {}
		vec3(double x, double y, double z) : x(x), y(y), z(z) {}
		vec3(vec3& v) : x(v.x), y(v.y), z(v.z) {}
		vec3& operator+=(vec3& v);
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
		void sort(int rang);
	public:
		mat3(double value = 0.0) : a(value, 0.0, 0.0), b(0.0, value, 0.0), c(0.0, 0.0, value) {}
		mat3(vec3& a, vec3& b, vec3& c) : a(a), b(b), c(c) {}
		mat3(mat3& m) : a(m.a), b(m.b), c(m.c) {}
		mat3& operator+=(mat3& m);
		void transpose();
	};

	void EvalCoef(Array& x, Array& y, matlib::mat3& A, matlib::vec3& b);
	void Solve_SLAE(mat3& A, vec3& b, vec3& c);
}
