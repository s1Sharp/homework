#include <gtest/gtest.h>
#include "task1309/part1.hpp"
#include "task1309/part2.hpp"
#include "task1309/part3.hpp"


TEST(Task1309, Part1_min) {
    // Expect equality.
    EXPECT_EQ((double)5.3, part1::min<double>(8.1, 5.3));
    EXPECT_EQ((float)5.3, part1::min(8.1f, 5.3f));
    EXPECT_EQ((double)5.0, part1::min<double>(8.1f, 5));
    EXPECT_TRUE((std::is_same<float,decltype(part1::min(8.1f, 5.3f))>::value));
    EXPECT_TRUE((std::is_same<double,decltype(part1::min(8.1, 5.3))>::value));
}


TEST(Task1309, Part1_max) {
    // Expect equality.
    EXPECT_EQ((double)8.1, part1::max<double>(8.1, 5.3));
    EXPECT_EQ((float)8.1, part1::max(8.1f, 5.3f));
    EXPECT_EQ((double)8.1, part1::max<double>(8.1, 5.f));
    EXPECT_TRUE((std::is_same<float,decltype(part1::max(8.1f, 5.3f))>::value));
    EXPECT_TRUE((std::is_same<double,decltype(part1::max(8.1, 5.3))>::value));
}


TEST(Task1309, Part1_swap) {
    // Expect equality.
    float t1 = 8.1f;
    float t2 = 5.3f;

    EXPECT_EQ((float)8.1f, t1);
    EXPECT_EQ((float)5.3f, t2);

    part1::swap(t1, t2);

    EXPECT_EQ((float)5.3f, t1);
    EXPECT_EQ((float)8.1f, t2);

    double t3 = 1.0;

    part1::swap(t3, t3);
    EXPECT_EQ((double)1.0, t3);
    EXPECT_TRUE((std::is_same<void, decltype(part1::swap(t3, t3))>::value));
}

TEST(Task1309, Part2_callback_int8_t) {
    // Expect equality.
    constexpr int array_size = 10;
    using data_type = int8_t;
    std::array<data_type, array_size> ArrayResult = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    std::array<data_type, array_size> Array = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    part2::iter(Array.data(), Array.size(), part2::custom_increment_print<data_type>);

    EXPECT_EQ(ArrayResult, Array);
    EXPECT_EQ(array_size, Array.size());
}

TEST(Task1309, Part2_callback_uint64_t) {
    // Expect equality.
    constexpr int array_size = 10;
    using data_type = uint64_t;
    std::array<data_type, array_size> ArrayResult = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    std::array<data_type, array_size> Array = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    part2::iter(Array.data(), Array.size(), part2::custom_increment_print<data_type>);

    EXPECT_EQ(ArrayResult, Array);
    EXPECT_EQ(array_size, Array.size());
}

TEST(Task1309, Part2_callback_double) {
    // Expect equality.
    constexpr int array_size = 10;
    using data_type = double;
    std::array<data_type, array_size> ArrayResult = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    std::array<data_type, array_size> Array = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    part2::iter(Array.data(), Array.size(), part2::custom_increment_print<data_type>);

    EXPECT_EQ(ArrayResult, Array);
    EXPECT_EQ(array_size, Array.size());
}

static inline double cdround(const double x, const size_t prec = 3) {
    return round(x * (prec * 10)) / (prec * 10);
}

template <typename T>
static bool equalComplex(const std::complex<T> &lhs, const std::complex<T> &rhs) {
    return (cdround(lhs.real()) == cdround(rhs.real()) && cdround(lhs.imag()) == cdround(rhs.imag()));
}

TEST(Task1309, Part3_boundary_cases_a0) {
    // Expect equality.
    using namespace part3;
    QuadEquation<double> q1(0, 1, 1);

    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::NOT_EXISTS_EQ);
}

TEST(Task1309, Part3_boundary_cases_b0_c0) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(0.0, 0.0);
    QuadEquation<double> q1(1, 0, 0);
    EXPECT_EQ(q1.m_z1, expect1);
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::ONE_REAL_EQ);
}

TEST(Task1309, Part3_boundary_cases_a0_b0_c0) {
    // Expect equality.
    using namespace part3;
    QuadEquation<double> q1(0, 0, 0);

    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::INF_EQ);
}

TEST(Task1309, Part3_boundary_cases_b0) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(0.0, 1.0);
    std::complex<double> expect2(0.0, -1.0);
    QuadEquation<double> q1(1, 0, 1);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_IMG_EQ);
}

TEST(Task1309, Part3_boundary_cases_c0) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(0.0, 0.0);
    std::complex<double> expect2(-1.0, 0.0);
    QuadEquation<double> q1(1, 1, 0);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_REAL_EQ);
}

TEST(Task1309, Part3_basic_funtions_two_img_1) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(-3.0 / 5,  4.0 / 5);
    std::complex<double> expect2(-3.0 / 5, -4.0 / 5);
    QuadEquation<double> q1(5, 6, 5);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_IMG_EQ);
}

TEST(Task1309, Part3_basic_funtions_two_img_2) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(3.0 / 2,  5.0 / 2);
    std::complex<double> expect2(3.0 / 2, -5.0 / 2);
    QuadEquation<double> q1(1, -3, 8.5);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_IMG_EQ);
}

TEST(Task1309, Part3_basic_funtions_two_img_3) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(0.0,  1.0);
    std::complex<double> expect2(0.0, -1.0);
    QuadEquation<double> q1(2, 0, 2);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_IMG_EQ);
}

TEST(Task1309, Part3_basic_funtions_two_img_4) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(-2.0,  5.0);
    std::complex<double> expect2(-2.0, -5.0);
    QuadEquation<double> q1(1, 4, 29);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_IMG_EQ);
}

TEST(Task1309, Part3_basic_funtions_two_img_5) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(-0.518844221105528,  0.722674173232695);
    std::complex<double> expect2(-0.518844221105528, -0.722674173232695);
    QuadEquation<double> q1(398, 413, 315);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_IMG_EQ);
}

TEST(Task1309, Part3_basic_funtions_two_real_1) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(-0.765549960006128, 0.0);
    std::complex<double> expect2(-205.734450039994,  0.0);
    QuadEquation<double> q1(2, 413, 315);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_REAL_EQ);
}

TEST(Task1309, Part3_basic_funtions_two_real_2) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(-1.14434539959896, 0.0);
    std::complex<double> expect2(-14.855654600401,  0.0);
    QuadEquation<double> q1(1, 16, 17);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::TWO_REAL_EQ);
}

TEST(Task1309, Part3_basic_funtions_one_real_1) {
    // Expect equality.
    using namespace part3;
    std::complex<double> expect1(-2.0 / 3, 0.0);
    std::complex<double> expect2(-2.0 / 3, 0.0);
    QuadEquation<double> q1(9, 12, 4);

    EXPECT_TRUE(equalComplex(q1.m_z1, expect1));
    EXPECT_TRUE(equalComplex(q1.m_z2, expect2));
    EXPECT_EQ(q1.isEquationExists, QuadEquation<double>::EQUATION_STATE::ONE_REAL_EQ);
}
