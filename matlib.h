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
		vec3(vec3 const& v) : x(v.x), y(v.y), z(v.z) {}
		vec3& operator=(vec3 const& v);
		vec3 operator+() const;
		vec3 operator-() const;
		vec3& operator+=(vec3 const& v);
		vec3& operator-=(vec3 const& v);
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
	public:
		double
			&a11, &a12, &a13,
			&a21, &a22, &a23,
			&a31, &a32, &a33;
		mat3(double value = 0.0) :
			a(value, 0.0, 0.0), b(0.0, value, 0.0), c(0.0, 0.0, value),
			a11(a.x), a12(b.x), a13(c.x),
			a21(a.y), a22(b.y), a23(c.y),
			a31(a.z), a32(b.z), a33(c.z)
		{}
		mat3(vec3 const& v1, vec3 const& v2, vec3 const& v3) :
			a(v1), b(v2), c(v3),
			a11(a.x), a12(b.x), a13(c.x),
			a21(a.y), a22(b.y), a23(c.y),
			a31(a.z), a32(b.z), a33(c.z)
		{}
		mat3(mat3 const& m) :
			a(m.a), b(m.b), c(m.c),
			a11(a.x), a12(b.x), a13(c.x),
			a21(a.y), a22(b.y), a23(c.y),
			a31(a.z), a32(b.z), a33(c.z)
		{}

		mat3& operator=(mat3 const& m);
		mat3 operator+() const;
		mat3 operator-() const;
		mat3& operator+=(mat3 const& m);
		mat3& operator-=(mat3 const& m);
		void transpose();
		void reverse();
		void sort(vec3& v, int rang);
		void print() const;
	};

	vec3 operator*(vec3 const& vector, double value);
	void EvalCoef(Array& x, Array& y, mat3& A, vec3& b);
	void Solve_SLAE(mat3& A, vec3& b, vec3& c);
}
