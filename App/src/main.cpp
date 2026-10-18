#include <iostream>
#include <Eigen/Dense>

using Matrix = Eigen::Matrix2d;

int main() {
	
    Matrix mat;

    mat(0, 0) = 1.0;
    mat(0, 1) = 2.0;
    mat(1, 0) = 3.0;
    mat(1, 1) = 4.0;

    std::cout << "Matrix:\n" << mat << "\n\n";


	return 0;
}