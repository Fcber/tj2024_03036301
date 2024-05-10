/****************************************************************\
 * @brief   Accessing, loading and base operations on images.   *
 * @file    image.h                                             *
 * @author  Zhang Yunlong                                       *
 * @date    Mar 5nd 2024                                        *
 * @mark                                                        *
\****************************************************************/

/***** DO NOT CHANGE, MODIFY OR DELETE THE FOLLOWING CODE *****/

#ifndef MATRIX_H
#define MATRIX_H

// C Standard Libraries
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cassert>

// C++ STL
#include <algorithm>
#include <string>
#include <vector>

class Matrix{

private:
    int m_rows = 0;
    int m_cols = 0;
    double *m_data = nullptr;

public:
    // Constructors
    Matrix() = default;
    Matrix(int rows, int cols = 1): m_rows(rows), m_cols(cols){
        m_data = (double *)calloc(m_rows*m_cols, sizeof(double));
    }

    // Destructor
    ~Matrix() { free(m_data); }

    // Copy constructor
    Matrix(Matrix const &m) {*this = m;}

    // Move constructor
    Matrix(Matrix &&m) noexcept {*this = std::move(m); }

    Matrix &operator= (Matrix const& m){
        if(this == &m) return *this;    // self assignment

        free(m_data);
        m_data = nullptr;

        m_rows = m.m_rows;
        m_cols = m.m_cols;
        m_data = (double *)calloc(m_rows * m_cols, sizeof(double));
        memcpy(m_data, m.m_data, sizeof(double)*m_rows*m_cols);
        return *this;
    }   

    // Move Assignment
    Matrix &operator=(Matrix &&m) noexcept{
        if(this == &m) return *this;

        free(m_data);

        m_rows = m.m_rows;
        m_cols = m.m_cols;
        m_data = m.m_data;

        m.m_data = nullptr;
        return *this;
    }

    // Accessor
    double &operator()(int row, int col) {return m_data[m_cols * row + col]; }
    double const& operator()(int row, int col) const { return m_data[m_cols * row + col]; }

    double &operator()(int i) {
        assert( m_rows == 1 || m_cols == 1);
        return m_data[i];
    }

    double const& operator()(int i) const { 
        assert( m_rows == 1 || m_cols == 1);
        return m_data[i];
    }

    int rows() const { return m_rows; }
    int cols() const { return m_cols; }

    // iterators
  
    double* begin() { return m_data; }
    double* end() { return m_data+m_rows*m_cols; }
  
    const double* begin() const { return m_data; }
    const double* end()   const { return m_data+m_rows*m_cols; }

    // Factories
    static Matrix zeros(int rows, int cols);
    static Matrix identity(int rows, int cols);
    static Matrix random(int rows, int cols);
    static Matrix augment(Matrix const& A);

    
    Matrix inverse() const;
    Matrix transpose() const;
    Matrix exp() const;
};

Matrix operator- (Matrix const& m);
Matrix operator+ (Matrix const& m);

Matrix operator- (Matrix const& lhs, Matrix const& rhs);
Matrix operator- (double lhs, Matrix const& rhs);
Matrix operator- (Matrix const& lhs, double rhs);
Matrix operator+ (Matrix const& lhs, Matrix const& rhs);
Matrix operator+ (double lhs, Matrix const& rhs);
Matrix operator+ (Matrix const& lhs, double rhs);

Matrix elementwiseDiv (Matrix const& lhs, Matrix const& rhs);
Matrix elementwiseMul (Matrix const& lhs, Matrix const& rhs);

Matrix operator* (Matrix const &lhs, Matrix const& rhs);

Matrix operator* (Matrix const& lhs, double rhs);
Matrix operator* (double lhs, Matrix const& rhs);

Matrix operator/ (Matrix const& lhs, double rhs);
Matrix operator/ (double lhs, Matrix const& rhs);

// lup
Matrix lupSolve(Matrix const& L, Matrix const& U, Matrix const& pi, Matrix const& b);
Matrix lupDecomposition(Matrix &A);

// Solve equation A*x = b
Matrix solveEquation(Matrix const& A, Matrix const& b);


#endif