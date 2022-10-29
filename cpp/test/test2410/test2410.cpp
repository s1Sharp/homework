#include <gtest/gtest.h>

#include <string>
#include "task2410/Fibonachi.hpp"
#include "task2410/monomial_2d.hpp"

TEST(Task2410, Fibonachi_eq) {
    // Expect equality.

    EXPECT_EQ(static_cast<uint64_t>(5), Fibonachi::Fibonachi<5>::value);
    EXPECT_EQ(static_cast<uint64_t>(55), Fibonachi::Fibonachi<10>::value);
}

TEST(Task2410, monomial_2d) {
    // Expect equality.
    constexpr double abs_error = 1e-6;

    const double mon_2d_integral_1_1_eq = 0.0416667;
    const double mon_2d_integral_1_1 = 1. / Factorial::monomial_2d<1, 1>::value;
    EXPECT_NEAR(mon_2d_integral_1_1_eq, mon_2d_integral_1_1, abs_error);

    const double mon_2d_integral_2_3_eq = 0.00238095;
    const double mon_2d_integral_2_3 = 1. / Factorial::monomial_2d<2, 3>::value;
    EXPECT_NEAR(mon_2d_integral_2_3_eq, mon_2d_integral_2_3, abs_error);

    const double mon_2d_integral_1_4_eq = 0.0047619;
    const double mon_2d_integral_1_4 = 1. / Factorial::monomial_2d<1, 4>::value;
    EXPECT_NEAR(mon_2d_integral_1_4_eq, mon_2d_integral_1_4, abs_error);

    const double mon_2d_integral_4_4_eq = 0.00015873;
    const double mon_2d_integral_4_4 = 1. / Factorial::monomial_2d<4, 4>::value;
    EXPECT_NEAR(mon_2d_integral_4_4_eq, mon_2d_integral_4_4, abs_error);
}