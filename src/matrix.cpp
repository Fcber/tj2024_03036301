#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>

#include <algorithm>
#include <thread>

#include <random>

#include "matrix.h"

Matrix operator-(Matrix const& m){
    Matrix ret(m.rows(), m.cols());
    for(int i=0;i<m.rows();++i) for(int j=0;j<m.cols();++j)
        ret(i,j) = -m(i,j);
    return ret;
}

Matrix operator+(Matrix const &m) {
    return m;
}

Matrix elementwiseDiv(Matrix const& lhs, Matrix const& rhs){
    assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
    Matrix ret(lhs.rows(), rhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = lhs(i,j)/rhs(i,j);
    return ret;
}

Matrix elementwiseMul(Matrix const& lhs, Matrix const& rhs){
    assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
    Matrix ret(lhs.rows(), rhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = lhs(i,j)*rhs(i,j);
    return ret;
}


void matrixMultiply(Matrix &m, Matrix const& lhs, Matrix const& rhs){
    for(int i=0;i<m.rows();++i)for(int j=0;j<m.cols();++j)for(int k=0;k<lhs.cols();++k)
        m(i,j) += lhs(i,k)*rhs(k,j);
}

Matrix operator*(Matrix const& lhs, Matrix const& rhs){
    Matrix ret(lhs.rows(), rhs.cols());
    matrixMultiply(ret, lhs, rhs);
    return ret;
}

Matrix operator+(Matrix const& lhs, Matrix const& rhs){
    assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
    Matrix ret(lhs.rows(), lhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = lhs(i,j)+rhs(i,j);
    return ret;
}

Matrix operator+(Matrix const& lhs, double rhs){
    Matrix ret(lhs.rows(), lhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<lhs.cols();++j)
        ret(i,j) = lhs(i,j)+rhs;
    return ret;
}

Matrix operator+(double lhs, Matrix const& rhs){
    Matrix ret(rhs.rows(), rhs.cols());
    for(int i=0;i<rhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = rhs(i,j)+lhs;
    return ret;
}

Matrix operator-(Matrix const& lhs, Matrix const& rhs){
    assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols());
    Matrix ret(lhs.rows(), lhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = lhs(i,j)-rhs(i,j);
    return ret;
}

Matrix operator-(Matrix const& lhs, double rhs){
    Matrix ret(lhs.rows(), lhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<lhs.cols();++j)
        ret(i,j) = lhs(i,j)-rhs;
    return ret;
}

Matrix operator-(double lhs, Matrix const& rhs){
    Matrix ret(rhs.rows(), rhs.cols());
    for(int i=0;i<rhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = lhs - rhs(i,j);
    return ret;
}

Matrix operator*(Matrix const& lhs, double rhs){
    Matrix ret(lhs.rows(), lhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<lhs.cols();++j)
        ret(i,j) = lhs(i,j) * rhs;
    return ret;
}

Matrix operator*(double lhs, Matrix const& rhs){
    Matrix ret(rhs.rows(), rhs.cols());
    for(int i=0;i<rhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = lhs * rhs(i,j);
    return ret;
}

Matrix operator/(Matrix const& lhs, double rhs){
    Matrix ret(lhs.rows(), lhs.cols());
    for(int i=0;i<lhs.rows();++i)for(int j=0;j<lhs.cols();++j)
        ret(i,j) = lhs(i,j) / rhs;
    return ret;
}

Matrix operator/(double lhs, Matrix const& rhs){
    Matrix ret(rhs.rows(), rhs.cols());
    for(int i=0;i<rhs.rows();++i)for(int j=0;j<rhs.cols();++j)
        ret(i,j) = lhs / rhs(i,j);
    return ret;
}

Matrix Matrix::zeros(int rows, int cols){
    return Matrix(cols,rows);
}

Matrix Matrix::identity(int rows, int cols){
    Matrix m(rows, cols);
    for(int i=0; i<rows && i<cols;++i){
        m(i,i)=1;
    }
    return m;
}

Matrix Matrix::augment(Matrix const& A){
    Matrix ret(A.rows(), A.cols()*2);
    for(int i=0;i<A.rows();++i)for(int j=0;j<A.cols();++j)
        ret(i,j) = A(i,j);
    for(int i=0;i<A.rows() && i<A.cols();++i)
        ret(i,i+A.cols()) = 1;
    return ret;
}

Matrix Matrix::exp() const{
    Matrix ret(m_rows, m_cols);
    for(int i=0;i<rows();++i)for(int j=0;j<cols();++j){
        ret(i,j) = std::exp(this->operator()(i,j));
    }
    return ret;
}

Matrix Matrix::transpose() const{
    Matrix ret(cols(),rows());
    for(int i=0;i<ret.rows();++i)for(int j=0;j<ret.cols();++j){
        ret(i,j)=this->operator()(j,i);
    }
    return ret;
}

Matrix Matrix::inverse(void) const {
  const Matrix &m = *this;
  assert(m.rows() == m.cols() && "Matrix not square\n");
  Matrix c = Matrix::augment(m);

  for (int k = 0; k < c.rows(); k++) {
    int index = -1;

    for (int i = k; i < c.rows(); i++)
      if (c(i, k) != 0) if (index == -1 || fabsl(c(i, k)) > fabsl(c(index, k)))
          index = i;

    if (index == -1) {
      printf("Can't invert. Matrix is singular\n");
      return Matrix::identity(m.rows(), m.cols());
    }

    for (int i = 0; i < c.cols(); i++) std::swap(c(k, i), c(index, i));
    for (int j = k + 1; j < c.cols(); j++)
      c(k, j) /= c(k, k);
    c(k, k) = 1;
    for (int i = k + 1; i < c.rows(); i++) {
      double s = -c(i, k);
      c(i, k) = 0;
      for (int j = k + 1; j < c.cols(); j++)
        c(i, j) += s * c(k, j);
    }
  }
  for (int k = c.rows() - 1; k > 0; k--)
    for (int i = 0; i < k; i++) {
      double s = -c(i, k);
      c(i, k) = 0;
      for (int j = k + 1; j < c.cols(); j++)c(i, j) += s * c(k, j);
    }
  Matrix inv(m.rows(), m.cols());
  for (int i = 0; i < m.rows(); i++)
    for (int j = 0; j < m.cols(); j++)
      inv(i, j) = c(i, j + m.cols());
  return inv;
}

Matrix lupSolve(Matrix const& L, Matrix const& U, Matrix const& pi, Matrix const& b){
    Matrix x(L.rows());
    for(int i = 0; i < L.rows(); ++i){
        x(i) = b(pi(i));
        for(int j = 0; j < i; ++j) x(i) -= L(i,j)*x(j);
    }
    for(int i = U.rows()-1; i>=0; --i){
        for(int j = i+1; j<U.cols();++j)
            x(i) -= U(i,j)*x(j);
        x(i)/=U(i,i);
    }

    return x;
}

Matrix lupDecomposition(Matrix &A){
    assert(A.rows() == A.cols() && "A MUST  be square matrix.");

    using namespace std;    // for swap

    Matrix pi(A.rows());
    for(int i=0;i<pi.rows();++i) pi(i)=i;

    for(int k=0;k<A.rows();++k){
        int p = -1;

        for(int i=k;k<A.rows();++i){
            if(p==-1 || abs(A(i,k)) > abs(A(p,k))) p = i;
        }

        assert(p!=-1 && "Singular Matrix.");
        swap(pi(k), pi(p));

        for(int i=0;i<A.cols();++i) swap(A(k,i), A(p,i));
        for(int i=k+1; i<A.rows();++i){
            A(i,k) = A(i,k)/A(k,k);
            for(int j=k+1; j<A.cols();++j)
                A(i,j)-=A(i,k)*A(k,j);
        }
    }

    return pi;
}

Matrix solveEquation(Matrix const& A, Matrix const& b){
    assert(A.rows() == b.rows());

    Matrix At = A.transpose();
    Matrix B = At * A;

    Matrix d = At * b;
    //Matrix pi = lupDecomposition(B);
    //return lupSolve(B,B,pi,d);

    return B.inverse()*d;
}