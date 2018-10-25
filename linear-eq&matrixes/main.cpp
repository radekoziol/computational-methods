#include <iostream>
#include "aghMatrix.h"

int main() 
{
//     initialize matrices using init value
//    AGHMatrix<double> mat1(4, 4, 2.3);
//    AGHMatrix<double> mat2(2, 3, 2.8);

//     Uncomment when implemented
//     AGHMatrix<double> mat3 = mat1 + mat2;
//    std::cout << mat3;

//    AGHMatrix<double> mat4 = mat1 * mat2;
//    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> pair = mat1.LUDecomposition();
//    AGHMatrix<double> mat5(pair.first);
//    AGHMatrix<double> mat6(pair.second);
//
//    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> pair2 = mat1.LUDecomposition();
//    AGHMatrix<double> mat7(pair2.first);
//    AGHMatrix<double> mat8(pair2.second);
//
//
//    std::cout << mat5;
//    std::cout << mat6;
//
//    std::cout << mat7;
//    std::cout << mat8;

    // initialize matrix using specified values
    std::vector<std::vector<double>> A { { 4.0, -2.0, 4.0, -2.0 , 8.0},
                                            { 3.0, 1.0, 4.0, 2.0, 7.0   },
                                            { 2.0, 4.0, 2.0, 1.0, 10.0   },
                                            { 2.0, -2.0, 4.0, 2.0, 2.0  }};

    std::vector<double> X = SolveWithGaussianElimination(AGHMatrix<double>(A));

    AGHMatrix<double> tmp = A;

    tmp.MakeMatrixLowerTriangular();
    std::cout << tmp;

    for(int i = 0; i < X.size() - 1; i ++)
        std::cout << X[i] << std::endl;


    return 0;
}