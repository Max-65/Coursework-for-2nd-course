#include <iostream>
#include "matlib.h"

//class Array {
//private:
//	int size;
//	double* arr;
//public:
//	Array(int size = 0, double allocator = 0.0) : size(size) {
//		arr = new double[this->size];
//		for (int i = 0; i < this->size; ++i) {
//			arr[i] = allocator;
//		}
//	}
//	~Array() {
//		delete[] arr;
//		arr = nullptr;
//	}
//	double& operator[](int i) const {
//		return arr[i];
//	}
//	void input() const {
//		for (int i = 0; i < size; ++i) {
//			std::cin >> arr[i];
//		}
//	}
//};

int const n = 6, m = 3;

int main() {
	matlib::Array x(n), y(n);

	std::cout << "Enter x values: ";
	x.input();
	std::cout << "Enter y values: ";
	y.input();

	matlib::mat3 A;
	matlib::vec3 b, c;
	
	matlib::EvalCoef(x, y, A, b);

	matlib::Solve_SLAE(A, b, c);

	return 0;
}
