#include <cmath>
#include "aghMatrix.h"

#define wrong_type_of_matrix 0

std::vector<std::vector<double>> MakeMatrixLowerTriangular(AGHMatrix<double> matrix);

// Parameter Constructor
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>> &mat) {
    matrix.resize(mat.size());
    for (unsigned i = 0; i < mat.size(); i++) {
        matrix[i].resize(mat[i].size());
        for (unsigned j = 0; j < mat[i].size(); j++) {
            matrix[i][j] = mat[i][j];
        }
    }
    rows = matrix.size();
    cols = matrix[1].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T &_initial) {
    matrix.resize(_rows);
    for (unsigned i = 0; i < matrix.size(); i++) {
        matrix[i].resize(_cols, _initial);
    }
    rows = _rows;
    cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T> &rhs) {
    matrix = rhs.matrix;
    rows = rhs.get_rows();
    cols = rhs.get_cols();
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned AGHMatrix<T>::get_rows() const {
    return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned AGHMatrix<T>::get_cols() const {
    return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
AGHMatrix<T> &AGHMatrix<T>::operator=(const AGHMatrix<T> &rhs) {
    if (&rhs == this)
        return *this;

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    matrix.resize(new_rows);
    for (unsigned i = 0; i < matrix.size(); i++) {
        matrix[i].resize(new_cols);
    }

    for (unsigned i = 0; i < new_rows; i++) {
        for (unsigned j = 0; j < new_cols; j++) {
            matrix[i][j] = rhs(i, j);
        }
    }
    rows = new_rows;
    cols = new_cols;

    return *this;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T &AGHMatrix<T>::operator()(const unsigned &row, const unsigned &col) {
    return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T &AGHMatrix<T>::operator()(const unsigned &row, const unsigned &col) const {
    return this->matrix[row][col];
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T> &rhs) {

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    matrix.resize(new_rows);

    for (unsigned i = 0; i < matrix.size(); i++) {
        matrix[i].resize(new_cols);
    }

    for (unsigned i = 0; i < new_rows; i++) {
        for (unsigned j = 0; j < new_cols; j++) {
            matrix[i][j] += rhs(i, j);
        }
    }
    rows = new_rows;
    cols = new_cols;

    return *this;
}


template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T> &rhs) {

    unsigned Xdim1 = rhs.get_rows();
    unsigned Ydim1 = rhs.get_cols();
    auto Xdim2 = static_cast<unsigned int>(matrix.size());
    unsigned Ydim2 = matrix[0].size();

    unsigned new_rows, new_cols, common_dim;

    if (Xdim1 == Ydim2) {
        new_cols = Ydim1;
        new_rows = Xdim2;
        common_dim = Xdim1;
    } else if (Ydim1 == Xdim2) {
        new_rows = Xdim1;
        new_cols = Ydim2;
        common_dim = Xdim1;
    } else {
        exit(-1);
    }

    const std::vector<std::vector<T>> tmp_matrix = matrix;

    matrix.resize(new_rows);

    for (unsigned i = 0; i < matrix.size(); i++) {
        matrix[i].resize(new_cols);
    }

    for (unsigned i = 0; i < new_rows; i++) {

        for (unsigned j = 0; j < new_cols; j++) {

            double sum = 0.0;

            for (unsigned k = 0; k < common_dim; k++) {
                sum += tmp_matrix[i][k] * rhs(k, j);
            }

            matrix[i][j] = sum;
        }
    }

    rows = new_rows;
    cols = new_cols;

    return *this;
}

template<typename T>
bool AGHMatrix<T>::IsSymmetric() {

    if (get_cols() != get_rows()) {
        exit(-1);
    }

    for (unsigned i = 0; i < get_rows(); i++) {

        for (unsigned j = 0; j < get_cols(); j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }

    return true;
}

template<typename T>
void AGHMatrix<T>::MakeMatrixLowerTriangular() {


    for (int i = 0; i <= matrix.size() - 1; i++) {

        for (int j = i + 1; j < matrix.size(); j++) {

            double t = -matrix[j][i] / matrix[i][i];

            for (int k = i; k <= matrix.size(); k++) {
                matrix[j][k] += t * matrix[i][k];
            }
        }
    }
}


std::vector<double> SolveWithGaussianElimination(AGHMatrix<double> A) {

    A.MakeMatrixLowerTriangular();

    std::vector<double> X(A.get_cols(), 0.0);

    for (auto i = static_cast<int>(A.get_rows() - 1); i >= 0; i--) {

        double sum = A(i
                ,A.get_cols() - 1);
        for (auto j = static_cast<int>(A.get_cols() - 1); j >= i + 1; j--) {
            sum -= A(i, j) * X[j];
        }

        X[i] = sum / A(i, i);

    }

    return X;
}


template<typename T>
std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> AGHMatrix<T>::LUDecomposition() {

    std::vector<std::vector<double>> A(matrix.size(), std::vector<double>(matrix.size(), 0.0));
    std::vector<std::vector<double>> B = A;

    for (int i = 0; i < matrix.size(); i++) {

        for (int j = i + 1; j < matrix.size(); j++) {

            double sumA = 0.0;
            double sumB = 0.0;

            for (int k = 1; k < i - 1; k++) {
                sumA += A[i][k] * B[k][j];
                sumB += A[j][k] * B[k][i];
            }

            A[i][j] = matrix[i][j] - sumA;
            B[j][i] = (matrix[i][j] - sumB) / (A[i][j]);

        }
    }


    return std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>(A, B);

}


template<typename T>
std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> AGHMatrix<T>::CholeskyDecomposition() {

    std::vector<std::vector<double>> L(matrix.size(), std::vector<double>(matrix.size(), 0.0));
    std::vector<std::vector<double>> L_T = L;

    for (int i = 0; i < matrix.size(); i++) {

        for (int j = i + 1; j < matrix.size(); j++) {

            double sumL1 = 0.0;
            double sumL2 = 0.0;

            for (int k = 1; k < j - 1; k++) {
                sumL1 += L[j][k] * L[j][k];
                sumL2 += L[i][k] * L[j][k];
            }

            if (i > j) {
                L[j][j] = sqrt(matrix[j][j] - sumL1);
                L_T[j][j] = L[j][j];
            }

            L[i][j] = (matrix[i][j] - sumL2) / (L[j][j]);
            L_T[j][i] = L[i][j];
        }
    }


    return std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>(L, L_T);

}


template<typename T>
double AGHMatrix<T>::Determinant() {

    if (get_rows() != get_cols()) {
        exit(-1);
    }

    double d = 1.0;

    for (int i = 1; i < matrix.size(); i++) {

        for (int j = 0; j < matrix.size(); j++) {

            double t = -matrix[j][i] / matrix[i][i];
            d *= t;
            for (int k = 0; k < matrix.size(); k++) {
                matrix[j][k] = t * matrix[i][k];
            }
        }
    }


    double diagonal_quotient = 1.0;
    for (int i = 0; i < matrix.size(); i++) {
        diagonal_quotient *= matrix[i][i];
    }

    return diagonal_quotient / d;

}


// Printing matrix
template<typename T>
std::ostream &operator<<(std::ostream &stream, const AGHMatrix<T> &matrix) {
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            stream << matrix(i, j) << ", ";
        }
        stream << std::endl;
    }
    stream << std::endl;
}

