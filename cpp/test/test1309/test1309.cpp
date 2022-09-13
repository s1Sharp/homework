#include <gtest/gtest.h>
#include "task1309/part1.hpp"
#include "task1309/part2.hpp"


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
