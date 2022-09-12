#pragma once
#include <type_traits>

namespace part1 {
    template <typename T>
    constexpr T min(const T& left, const T& right) {
        return (left < right) ? left : right;
    }

    template <typename T>
    constexpr T max(const T& left, const T& right) {
        return (left > right) ? left : right;
    }

    template <typename T>
    void swap(T& left, T& right) {
        T tmp(std::move(right));
        right = std::move(left);
        left = std::move(tmp);

        return;
    }
}