#include <iostream>
#include "aghMatrix.h"


double fRand(double fMin, double fMax) {
    double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void printWithRows(AGHMatrix<double> matrix) {

    std::cout << std::endl;

    for (unsigned int i = 0; i < matrix.get_rows(); i++) {

        std::cout << std::endl;
        std::cout << "R: " << i << std::endl;
        std::cout << std::endl;

        for (unsigned int j = 0; j < matrix.get_cols(); j++) {

            std::cout << matrix(i, j) << std::endl;

        }

    }

    std::cout << std::endl;

}

AGHMatrix<double> generateMatrix(unsigned int rows, unsigned int columns) {


    std::vector<std::vector<double>> A(rows, std::vector<double>(columns, 0.0));
    AGHMatrix<double> B = A;

    bool firstIteration = true;
    while (!B.isDiagonallyDominant() || firstIteration) {
        firstIteration = false;

        for (unsigned int i = 0; i < rows; i++) {

            for (unsigned int j = 0; j < columns; j++) {
                B(i, j) = fRand(-1.0, 5.0);
            }
        }
    }


    return B;
}


int main() {


    for (unsigned int i = 2; i <= 32; i = i + 3) {
        std::cout << std::endl;
        std::cout << 5 << "x" << 5 << std::endl;

        const AGHMatrix<double> &A = generateMatrix(5, 5 + 1);

        printWithRows(A);

        std::cout << std::endl;
        std::cout << "Real solution" << std::endl;
        std::vector<double> X = SolveWithGaussianElimination(A);
        for (unsigned int j = 0; j < X.size() - 1; j++)
            std::cout << X[j] << std::endl;

        std::cout << std::endl;
        std::cout << "Jacobi approximation" << std::endl;
        std::vector<double> X1 = SolveWithJacobiMethod(A);
        for (unsigned int j = 0; j < X.size() - 1; j++)
            std::cout << X1[j] << std::endl;

        std::cout << std::endl;
        std::cout << "Gaus-Seidel approximation" << std::endl;
        std::vector<double> X2 = SolveWithGaussSeidelMethod(A);
        for (unsigned int j = 0; j < X.size() - 1; j++)
            std::cout << X2[j] << std::endl;

        std::cout << std::endl;
        std::cout << "SOR approximation" << std::endl;
        std::vector<double> X3 = SolveWithSORMethod(A, 2.0);
        for (unsigned int j = 0; j < X.size() - 1; j++)
            std::cout << X3[j] << std::endl;


    }


    return 0;
}

