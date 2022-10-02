#include <gtest/gtest.h>
#include "task2609/part1.hpp"


TEST(Task2609, Part1_Matrix) {
    // Expect equality.
    auto m1 = part1::Matrix<double>(std::vector<std::vector<double>>({{1, 2}, {3 , 4}}));
    auto m2 = part1::Matrix<double>(std::vector<std::vector<double>>({{2, 2}, {2 , 2}}));
    std::vector<std::vector<double>> expectResult = {{3, 4}, {5, 6}};

    auto mResult = part1::sum(m1, m2);
    EXPECT_EQ(expectResult, mResult.mData);
}

TEST(Task2609, Part1_Complex) {
    // Expect equality.
    auto c1 = part1::Complex(1.0, 2.0);
    auto c2 = part1::Complex(3.0, 4.0);

    const double expectResultRe = 4;
    const double expectResultIm = 6;

    auto cResult = part1::sum(c1, c2);
    EXPECT_EQ(expectResultRe, cResult.mR);
    EXPECT_EQ(expectResultIm, cResult.mI);
}

TEST(Task2609, Part1_std_String) {
    // Expect equality.
    auto s1 = std::string("Hello ");
    auto s2 = std::string("World\n");

    const auto expectString = std::string("Hello World\n");

    auto sResult = part1::sum(s1, s2);
    EXPECT_EQ(expectString, sResult);
}

TEST(Task2609, Part1_c_String) {
    // Expect equality.
    const char cs1[] = "Hello \0";
    const char cs2[] = "World\n\0";

    const char expect_c_String[] = "Hello World\n\0";
    const int32_t expectResult = 0;

    size_t retry = 10000;
    while (retry) {
        retry--;
        auto csResult = part1::sum(cs1, cs2);
        EXPECT_EQ(expectResult, strcmp(csResult, expect_c_String));
        free(csResult);
    }
}