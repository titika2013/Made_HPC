
#include <random>
#include <chrono>
#include "src/matrix.h"

using task::Matrix;
using namespace std::chrono;

double RandomDouble()
{
    static std::mt19937 rand(std::random_device{}());

    std::uniform_real_distribution<double> dist{-10., 10.};
    return dist(rand);
}

Matrix RandomMatrix(size_t rows, size_t cols)
{
    Matrix temp(rows, cols);
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            temp[row][col] = RandomDouble();
        }
    }
    return temp;
}

int main(int argc, char **argv)
{
    size_t N = std::atol(argv[1]);
    auto a = RandomMatrix(N, N);
    auto b = RandomMatrix(N, N);

    auto start = high_resolution_clock::now();

    auto res = a * b;
    // auto res_1 = matmul_ikj(a, b); разный  порядок циклов
    // auto res_2 = matmul_jik(a, b);
    auto end = high_resolution_clock::now();
    // Get ending timepoint
    auto stop = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << ": N = " << N;
    std::cout << " Time taken " << duration.count() << " microseconds"
              << "\n";

    return 0;
}