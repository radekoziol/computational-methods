#include <iostream>
#include "aghMatrix.h"

int main() 
{
//     initialize matrices using init value
    AGHMatrix<double> mat1(4, 2, 1.2);
    AGHMatrix<double> mat2(2, 3, 2.8);

//     Uncomment when implemented
//     AGHMatrix<double> mat3 = mat1 + mat2;
//    std::cout << mat3;

    AGHMatrix<double> mat4 = mat1 * mat2;
    std::cout << mat4;

    // initialize matrix using specified values
//    std::vector<std::vector<double>> init { { 1.0, 2.0, 3.0 },
//                                            { 4.0, 5.0, 6.0 },
//                                            { 7.0, 8.0, 9.0 } };
//
//    AGHMatrix<double> mat4(init);
//    std::cout << ;
    return 0;
}