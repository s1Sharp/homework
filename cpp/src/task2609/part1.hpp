#pragma once

#include <type_traits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <cmath>
#include <cstring>
#include <string>

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
        Matrix(std::vector<std::vector<double>> m): mRows(m.size()), mCols(m[0].size()) {
            for (size_t i = 0; i < mRows; i++) {
                mData.push_back(m[i]);
            }
        };

        Matrix(Matrix& rhs): mRows(rhs.mData.size()), mCols(rhs.mData[0].size()) {
            for (size_t i = 0; i < mRows; i++) {
                mData.push_back(rhs.mData[i]);
            }
        };

        Matrix* operator+=(Matrix& rhs) {
            if (rhs.mRows != this->mRows || rhs.mCols != this->mCols) {
                throw std::runtime_error("size of matrix not equal");
            }
            for (size_t i = 0; i < mRows; i++) {
                for (size_t j = 0; j < mCols; j++) {
                    this->mData[i][j] += rhs.mData[i][j];
                }
            }
            return this;
        }

    };

    class Complex {
        public:
            double mR;
            double mI;
        Complex(double r, double i) : mR(r), mI(i) {};
        Complex(Complex& rhs) : mR(rhs.mR), mI(rhs.mI) {};
        Complex* operator+=(Complex& rhs) {
            this->mR += rhs.mR;
            this->mI += rhs.mI;
            return this;
        }
    };

    template <typename T>
    T sum(T &lhs, T &rhs) {
        return T(lhs += rhs);
    }

    template <>
    Complex sum(Complex &lhs, Complex &rhs) {
        lhs += rhs;
        return Complex(lhs);
    }

    template <>
    Matrix<double> sum(Matrix<double> &lhs, Matrix<double> &rhs) {
        lhs += rhs;
        return Matrix<double>(lhs);
    }

    template <>
    std::string sum(std::string &lhs, std::string &rhs) {
        return lhs += rhs;
    }

    char* sum(const char * lhs, const char * rhs) {
        if (lhs == nullptr || rhs == nullptr) {
            return nullptr;
        }
        const size_t lhs_len = strlen(lhs) + 1;
        const size_t rhs_len = strlen(rhs) + 1;
        const size_t newLen = lhs_len + rhs_len + 1;
        char* p_newStr = (char *)calloc(newLen, sizeof(char));
        strcpy(p_newStr, lhs);
        strcat(p_newStr, rhs);
        return p_newStr;
    }

    char* sum(char * lhs, char * rhs) {
        return sum((const char *)lhs, (const char *)rhs);
    }
}
