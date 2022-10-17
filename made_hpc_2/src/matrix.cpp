#include "matrix.h"
#include "cmath"

using namespace task;
namespace task
{
  Matrix::Matrix(size_t rows, size_t cols)
  {
    m_rows = rows;
    m_columns = cols;
    new_space();
    if (rows == cols)
    {
      for (int i = 0; i < m_rows; ++i)
      {
        for (int j = 0; j < m_columns; ++j)
        {
          matrix[i][j] = 1;
        }
      }
    }
    else
    {
      for (int i = 0; i < m_rows; ++i)
      {
        for (int j = 0; j < m_columns; ++j)
        {
          matrix[i][j] = (i == j) ? 1 : 0;
        }
      }
    }
  }

  Matrix::Matrix()
  {
    m_rows = 1;
    m_columns = 1;
    new_space();
    matrix[0][0] = 1;
  }

  Matrix::Matrix(const Matrix &copy)
  {
    m_rows = copy.m_rows;
    m_columns = copy.m_columns;
    new_space();
    for (int i = 0; i < m_rows; ++i)
    {
      for (int j = 0; j < m_columns; ++j)
      {
        matrix[i][j] = copy.matrix[i][j];
      }
    }
  }

  Matrix::~Matrix()
  {
    for (int i = 0; i < m_rows; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  Matrix &Matrix::operator=(const Matrix &a)
  {
    if (this == &a)
    {
      return *this;
    }

    if (m_rows != a.m_rows || m_columns != a.m_columns)
    {
      for (int i = 0; i < m_rows; ++i)
      {
        delete[] matrix[i];
      }
      delete[] matrix;

      m_rows = a.m_rows;
      m_columns = a.m_columns;
      new_space();
    }

    for (int i = 0; i < m_rows; ++i)
    {
      for (int j = 0; j < m_columns; ++j)
      {
        matrix[i][j] = a.matrix[i][j];
      }
    }
    return *this;
  }

  double &Matrix::get(size_t row, size_t col)
  {

    if (row >= this->m_rows || col >= this->m_columns || row < 0 || col < 0)
    {
      throw OutOfBoundsException();
    }

    else
    {

      return matrix[row][col];
    }
  }

  const double &Matrix::get(size_t row, size_t col) const
  {

    if (row >= this->m_rows || col >= this->m_columns || row < 0 || col < 0)
    {
      throw OutOfBoundsException();
    }

    else
    {
      return matrix[row][col];
    }
  }

  void Matrix::set(size_t row, size_t col, const double &value)
  {

    if (row >= this->m_rows || col >= this->m_columns || row < 0 || col < 0)
    {
      throw OutOfBoundsException();
    }

    else
    {
      matrix[row][col] = value;
    }
  }

  void Matrix::resize(size_t new_rows, size_t new_cols)
  {
    double **new_mat;
    new_mat = new double *[new_rows];
    for (int i = 0; i < new_rows; ++i)
    {
      new_mat[i] = new double[new_cols];
    }
    if (new_rows >= m_rows)
    {
      new_rows = m_rows;
    }
    if (new_cols <= m_columns)
    {
      new_cols = m_columns;
    }
    for (int i = 0; i < new_rows; ++i)
    {

      for (int j = 0; j < new_cols; ++j)
      {
        new_mat[i][j] = matrix[i][j];
      }
    }

    for (int i = 0; i < this->m_rows; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;

    matrix = new_mat;
    new_mat = nullptr;
    m_rows = new_rows;
    m_columns = new_cols;
  }

  Matrix &Matrix::operator+=(const Matrix &a)
  {
    if (a.m_rows != this->m_rows || a.m_columns != this->m_columns)
    {
      throw SizeMismatchException();
      return *this;
    }
    for (int i = 0; i < m_rows; ++i)
    {
      for (int j = 0; j < m_columns; ++j)
      {
        matrix[i][j] += a.matrix[i][j];
      }
    }
    return *this;
  }
  Matrix &Matrix::operator-=(const Matrix &a)
  {
    if (a.m_rows != this->m_rows || a.m_columns != this->m_columns)
    {
      throw SizeMismatchException();
      return *this;
    }
    for (int i = 0; i < m_rows; ++i)
    {
      for (int j = 0; j < m_columns; ++j)
      {
        matrix[i][j] -= a.matrix[i][j];
      }
    }
    return *this;
  }

  Matrix &Matrix::operator*=(const Matrix &a)
  {
    if (this->m_columns != a.m_rows)
    {
      throw SizeMismatchException();
      return *this;
    }
    Matrix temp(this->m_rows, a.m_columns);
    for (int i = 0; i < temp.m_rows; ++i)
    {
      for (int j = 0; j < temp.m_columns; ++j)
      {
        for (int k = 0; k < m_columns; ++k)
        {
          temp.matrix[i][j] += (matrix[i][k] * a.matrix[k][j]);
        }
      }
    }
    return *this = temp;
  }

  Matrix &Matrix::operator*=(const double &number)
  {
    for (int i = 0; i < m_rows; ++i)
    {
      for (int j = 0; j < m_columns; ++j)
      {
        matrix[i][j] *= number;
      }
    }
    return *this;
  }

  Matrix Matrix::operator+(const Matrix &a) const
  {

    if (a.m_rows != this->m_rows || a.m_columns != this->m_columns)
    {
      throw SizeMismatchException();
      return *this;
    }

    Matrix temp(a.m_rows, a.m_columns);

    for (int i = 0; i < a.m_rows; ++i)
    {
      for (int j = 0; j < a.m_columns; ++j)
      {
        temp.matrix[i][j] = this->matrix[i][j] + a.matrix[i][j];
      }
    }

    return temp;
  }

  Matrix Matrix::operator-(const Matrix &a) const
  {

    if (a.m_rows != this->m_rows || a.m_columns != this->m_columns)
    {
      throw SizeMismatchException();
      return *this;
    }

    Matrix temp(a.m_rows, a.m_columns);

    for (int i = 0; i < a.m_rows; ++i)
    {
      for (int j = 0; j < a.m_columns; ++j)
      {
        temp.matrix[i][j] = this->matrix[i][j] - a.matrix[i][j];
      }
    }

    return temp;
  }

  Matrix Matrix::operator*(const Matrix &a) const
  {
    if (this->m_columns != a.m_rows)
    {
      throw SizeMismatchException();
      return *this;
    }

    Matrix temp(this->m_rows, a.m_columns);
    for (int i = 0; i < temp.m_rows; ++i)
    {
      for (int j = 0; j < temp.m_columns; ++j)
      {
        for (int k = 0; k < m_columns; ++k)
        {
          temp.matrix[i][j] = (matrix[i][k] * a.matrix[k][j]);
        }
      }
    }
    return temp;
  }

  Matrix Matrix::operator*(const double &a) const
  {
    Matrix temp(this->m_rows, this->m_columns);
    for (int i = 0; i < m_rows; ++i)
    {
      for (int j = 0; j < m_columns; ++j)
      {
        temp.matrix[i][j] = matrix[m_rows][m_columns] * a;
      }
    }
    return temp;
  }

  bool Matrix::operator==(const Matrix &a) const
  {
    if (a.m_rows != this->m_rows || a.m_columns != this->m_columns)
      return false;
    for (int i = 0; i < m_rows; ++i)
    {
      for (int j = 0; j < m_columns; ++j)
      {
        double z0 = fabs(a.matrix[i][j] - matrix[i][j]);
        double z1 = fabs(a.matrix[i][j]);
        double z2 = fabs(matrix[i][j]);
        if (fabs(a.matrix[i][j] - matrix[i][j]) > EPS)
        {
          return false;
        }
      }
    }

    return true;
  }

  bool Matrix::operator!=(const Matrix &a) const
  {
    return !(*this == a);
  }

  void Matrix::new_space()
  {
    matrix = new double *[this->m_rows];
    for (int i = 0; i < this->m_rows; ++i)
    {
      matrix[i] = new double[m_columns];
    }
  }

  Matrix matmul_ikj(const Matrix &a, const Matrix &b)
  {
    if (a.m_columns != b.m_rows)
    {
      throw SizeMismatchException();
      return a;
    }

    Matrix temp(a.m_rows, b.m_columns);
    for (int i = 0; i < temp.m_rows; ++i)
    {
      for (int k = 0; k < temp.m_columns; ++k)
      {
        for (int j = 0; j < a.m_columns; ++j)
        {
          temp.matrix[i][j] = (a.matrix[i][k] * b.matrix[k][j]);
        }
      }
    }
    return temp;
  }

  Matrix matmul_jik(const Matrix &a, const Matrix &b)
  {
    if (a.m_columns != b.m_rows)
    {
      throw SizeMismatchException();
      return a;
    }

    Matrix temp(a.m_rows, b.m_columns);
    for (int j = 0; j < temp.m_rows; ++j)
    {
      for (int i = 0; i < temp.m_columns; ++i)
      {
        for (int k = 0; k < a.m_columns; ++k)
        {
          temp.matrix[i][j] = (a.matrix[i][k] * b.matrix[k][j]);
        }
      }
    }
    return temp;
  }

} // namespace task
