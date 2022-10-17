#pragma once

#include <vector>
#include <iostream>

namespace task
{

    const double EPS = 1e-6;

    class OutOfBoundsException : public std::exception
    {
    };
    class SizeMismatchException : public std::exception
    {
    };

    class Matrix
    {

    public:
        double **matrix;
        size_t m_rows;
        size_t m_columns;
        Matrix();
        ~Matrix();
        Matrix(size_t rows, size_t cols);
        Matrix(const Matrix &copy);

        Matrix &operator=(const Matrix &a);

        double &get(size_t row, size_t col);
        const double &get(size_t row, size_t col) const;
        void set(size_t row, size_t col, const double &value);
        void resize(size_t new_rows, size_t new_cols);

        double *operator[](size_t row) { return matrix[row]; }
        const double *operator[](size_t row) const { return matrix[row]; }

        Matrix &operator+=(const Matrix &a);
        Matrix &operator-=(const Matrix &a);
        Matrix &operator*=(const Matrix &a);
        Matrix &operator*=(const double &number);

        Matrix operator+(const Matrix &a) const;
        Matrix operator-(const Matrix &a) const;
        Matrix operator*(const Matrix &a) const;
        Matrix operator*(const double &a) const;

        bool operator==(const Matrix &a) const;
        bool operator!=(const Matrix &a) const;

        void new_space();
        friend Matrix operator*(const double &a, const Matrix &b)
        {
            return b * a;
        }

        friend std::ostream &operator<<(std::ostream &output, const Matrix &matrix_)
        {
            for (int i = 0; i < matrix_.m_rows; ++i)
            {
                for (int j = 0; j < matrix_.m_columns; ++j)
                {
                    output << matrix_.matrix[i][j] << std::endl;
                }
                output << std::endl;
            }
            return output;
        }

        friend std::istream &operator>>(std::istream &input, Matrix &matrix_)
        {
            int new_rows;
            int new_columns;
            input >> new_rows;
            input >> new_columns;
            double **new_mat;
            new_mat = new double *[new_rows];
            if (new_rows != matrix_.m_rows && new_columns != matrix_.m_columns)
            {

                for (int i = 0; i < new_rows; ++i)
                {
                    new_mat[i] = new double[new_columns];
                }
                for (int i = 0; i < matrix_.m_rows; ++i)
                {
                    delete[] matrix_.matrix[i];
                }
                delete[] matrix_.matrix;
                matrix_.matrix = new_mat;
                new_mat = nullptr;
                matrix_.m_rows = new_rows;
                matrix_.m_columns = new_columns;
            }
            for (int i = 0; i < matrix_.m_rows; ++i)
            {
                for (int j = 0; j < matrix_.m_columns; ++j)
                {
                    input >> matrix_.matrix[i][j];
                }
            }
            return input;
        }
    };
    Matrix matmul_ikj(const Matrix &a, const Matrix &b);
    Matrix matmul_jik(const Matrix &a, const Matrix &b);
} // namespace task
