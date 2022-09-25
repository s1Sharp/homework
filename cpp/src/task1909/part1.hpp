#pragma once

#include <type_traits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <cmath>

namespace part1 {
    template <typename T>
    class Matrix 
    {
    public:
    size_t mRows;
    size_t mCols;
    std::vector<std::vector<double>> mData;
        Matrix(size_t n, size_t m): mRows(n), mCols(m) {
            if (mRows != mCols) {
                mRows = 0; mCols = 0;
                return;
            }
            mData = std::vector<std::vector<double>>(mCols);
            std::random_device rnd_device;
            // Specify the engine and distribution.
            std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
            std::uniform_real_distribution<T> dist {1, 52};
            
            auto gen = [&dist, &mersenne_engine](){
                        return dist(mersenne_engine);
                    };
            for (auto& v: mData) {
                v = std::vector<double>(mRows);
                std::generate(v.begin(), v.end(), gen);
            }
        };
        double det() {
            return CalcDeterminant(this->mData);
        }

        static double CalcDeterminant(std::vector<std::vector<double>> matrix)
        {
            // std::cout << "matrix size = " << matrix.size() << std::endl;
            // this function calculate determinant of matrix
            // it's a recursive function,
            // that can handle matrix of any dimension
            double det = 0;

            if (matrix.size() <= 0 || matrix[0].size()<= 0) {
                throw std::runtime_error("matrix size equal 0"); // error
            }

            if (matrix.size() == 1) {
                return matrix[0][0]; // no calculation needed
            }
            else if (matrix.size() == 2) {
                // in this case we calculate the determinant of a 2-dimensional matrix
                det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
                return det;
            }
            else {
                // in this case we calculate the determinant of a squared matrix that have
                for (int p = 0; p < matrix[0].size(); p++) {
                    // this loop iterate on each elements of the first row in the matrix.
                    // at each element we cancel the row and column it exist in
                    // and form a matrix from the rest of the elements in the matrix
                    std::vector<std::vector<double>> TempMatrix; // to hold the shaped matrix;
                    for (int i = 1; i < matrix.size(); i++) {
                        // iteration will start from row one cancelling the first row values
                        std::vector<double> TempRow;
                        for (int j = 0; j < matrix[i].size(); j++) {
                            // iteration will pass all cells of the i row excluding the j 
                            // value that match p column
                            if (j != p) {
                            TempRow.push_back(matrix[i][j]);//add current cell to TempRow 
                            }
                        }
                        if (TempRow.size() > 0) {
                            TempMatrix.push_back(TempRow);
                        }
                    }
                    det = det + matrix[0][p] * pow(-1, p) * CalcDeterminant(TempMatrix);
                    //then we calculate the value of determinant by using a recursive way
                    //where we re-call the function by passing to it the new formed matrix
                    //we keep doing this until we get our determinant
                }
                return det;
            }
        };
    };

    class Complex {
        public:
            double mR;
            double mI;
        Complex(double r, double i) : mR(r), mI(i) {};
        double det() { 
            return CalcDeterminant(this->mR, this->mI);
        }
        static double CalcDeterminant(double r, double i) {
            return std::sqrt(r * r + i * i);
        }
    };

    template <typename T>
    decltype(auto) modul(T x) = delete;

    template <>
    decltype(auto) modul(Complex x) {
        return x.det();
    }

    template <>
    decltype(auto) modul(Matrix<double> x) {
        return x.det();
    }
}
