#include <iostream>
#include "matlib.h"

int const n = 6, m = 3;

int main() {
	matlib::Array x(n), y(n), y1(n), d(n);
	double max_d(0), approx_crit(0);
	int max_d_i(0);

	std::cout << "Enter x values: ";
	std::cin >> x;
	std::cout << "Enter y values: ";
	std::cin >> y;

	matlib::mat3 A;
	matlib::vec3 b, c;
	
	matlib::EvalCoef(x, y, A, b);

	matlib::SolveSLAE(A, b, c);

	std::cout.precision(3);
	std::cout << std::fixed;
	std::cout << "A\n" << A << '\n';
	std::cout << "\nb\n" << b.x << ' ' << b.y << ' ' << b.z << '\n';
	std::cout << "\nc\n" << c.x << ' ' << c.y << ' ' << c.z << '\n';

	matlib::Approx(c, x, y1);
	std::cout << "\nApproximating function values: " << y1 << '\n';

	matlib::ApproxQuality(y, y1, d, max_d, max_d_i, approx_crit);
	std::cout << "\nDivergence values: " << d << '\n';
	std::cout << "\nMaximal divergence = " << max_d << " at x = " << x[max_d_i] << '\n';
	std::cout << "\nApprximation criterion = " << approx_crit << '\n';

	return 0;
}

/*
1.1 2.1 3.1 4.1 5.1 6.1
0.1 0.4 0.9 1.6 2.5 3.6

*/
