#pragma once
#include <array>

namespace part2 {
    template <typename T, typename F>
    void iter(T* p_array, size_t array_size, F callback) {
        for (size_t i = 0; i < array_size; i++) {
            (void)callback(p_array[i]);
        }
    }

    template <typename T>
    void custom_increment_print(T& val) {
#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
        val++;
#else
        std::cout << "Val before = " << val << std::endl;
        val++;
        std::cout << "Val after = " << val << std::endl;
#endif
    }
}