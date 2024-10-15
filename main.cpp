#include <iostream>
#include "matlib.h"

int const n = 6, m = 3;

int main() {
	matlib::Array x(n), y(n);

	std::cout << "Enter x values: ";
	x.input();
	std::cout << "Enter y values: ";
	y.input();

	matlib::mat3 A;
	matlib::vec3 b, c(0, 1, 2);
	
	matlib::EvalCoef(x, y, A, b);

	matlib::Solve_SLAE(A, b, c);

	std::cout << '\n' << c.x << ' ' << c.y << ' ' << c.z << '\n';
	return 0;
}

/*
1.1 2.1 3.1 4.1 5.1 6.1
0.1 0.4 0.9 1.6 2.5 3.6

*/
