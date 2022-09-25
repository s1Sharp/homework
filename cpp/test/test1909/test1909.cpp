#include <gtest/gtest.h>
#include "task1909/part1.hpp"

class MatrixMultipleParametersTests :public ::testing::TestWithParam<std::tuple<size_t, size_t>> {};

TEST_P(MatrixMultipleParametersTests, Part1_matrix_NxN) {
    size_t n = std::get<0>(GetParam());
    size_t m = std::get<1>(GetParam());

    auto matrix = part1::Matrix<double>(n, m);
    EXPECT_EQ((size_t)n, matrix.mRows);
    EXPECT_EQ((size_t)m, matrix.mCols);

    EXPECT_EQ((double)matrix.det(), (double)part1::modul(matrix));
    EXPECT_EQ((double)part1::Matrix<double>::CalcDeterminant(matrix.mData), (double)part1::modul(matrix));
}

INSTANTIATE_TEST_SUITE_P(
        Part1_matrix_NxN,
        MatrixMultipleParametersTests,
        ::testing::Values(
                std::make_tuple(1, 1),
                std::make_tuple(2, 2),
                std::make_tuple(3, 3),
                std::make_tuple(4, 4),
                std::make_tuple(5, 5)));

TEST(Task1909, Part1_matrix_throw) {
    // Expect equality.
    size_t n = 1;
    size_t m = 2;
    auto matrix = part1::Matrix<double>(n, m);

    EXPECT_EQ((size_t)0, matrix.mRows);
    EXPECT_EQ((size_t)0, matrix.mCols);

    EXPECT_THROW({
        try
        {
            (double)part1::modul(matrix);
        }
        catch( const std::runtime_error& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "matrix size equal 0", e.what() );
            throw;
        }
    }, std::runtime_error );
}

class ComplexMultipleParametersTests :public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(ComplexMultipleParametersTests, Part1_complex_r_i) {
    // Expect equality.
    static const double abs_error = 0.001;
    double r = std::get<0>(GetParam());
    double i = std::get<1>(GetParam());
    double expected = std::get<2>(GetParam());

    auto complex = part1::Complex(r, i);
    EXPECT_EQ((double)r, complex.mR);
    EXPECT_EQ((double)i, complex.mI);

    EXPECT_NEAR((double)expected, (double)part1::modul(complex),
        abs_error);
    EXPECT_NEAR((double)complex.det() , (double)part1::modul(complex),
        abs_error);
    EXPECT_NEAR((double)part1::Complex::CalcDeterminant(complex.mR, complex.mI), (double)part1::modul(complex),
        abs_error);
    EXPECT_NEAR((double)expected, (double)part1::modul(complex),
        abs_error);
}

INSTANTIATE_TEST_SUITE_P(
        Part1_complex_r_i,
        ComplexMultipleParametersTests,
        ::testing::Values(
                std::make_tuple(1, 1, (double)1.41421),
                std::make_tuple(2, 2, (double)2.828427),
                std::make_tuple(4, 5, (double)6.4031),
                std::make_tuple(122, 344, (double)364.993)));
