#ifndef __AGH_MATRIX_H
#define __AGH_MATRIX_H

#include <vector>
#include <iostream>

template<typename T>
class AGHMatrix {
private:
    std::vector<std::vector<T>> matrix;
    unsigned rows;
    unsigned cols;

public:
    AGHMatrix(const std::vector<std::vector<T>> &matrix);

    AGHMatrix(unsigned _rows, unsigned _cols, const T &_initial);

    AGHMatrix(const AGHMatrix<T> &rhs);

    virtual ~AGHMatrix() = default;

    // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
    AGHMatrix<T> &operator=(const AGHMatrix<T> &rhs);

    // Matrix mathematical operations                                                                                                                                                                                               
    AGHMatrix<T> operator+(const AGHMatrix<T> &rhs);

    AGHMatrix<T> operator*(const AGHMatrix<T> &rhs);

    // Access the individual elements                                                                                                                                                                                               
    T &operator()(const unsigned &row, const unsigned &col);

    const T &operator()(const unsigned &row, const unsigned &col) const;

    // Printing matrix
    std::ostream &operator<<(const AGHMatrix<T> &matrix);

    // Access the row and column sizes                                                                                                                                                                                              
    unsigned get_rows() const;

    unsigned get_cols() const;


    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> LUDecomposition();

    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> CholeskyDecomposition();


    bool isDiagonallyDominant();

    bool IsSymmetric();

    double Determinant();

    void MakeMatrixLowerTriangular();

    std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<double>>, std::vector<std::vector<double>>>
    DLUDecomposition();
};

#include "aghMatrix.cpp"

#endif