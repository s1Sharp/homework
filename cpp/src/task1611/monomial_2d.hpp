#pragma once

#include <stdint.h>

namespace Factorial {
    template<uint64_t N>
    struct factorial {
        static const uint64_t value = N * factorial<N - 1>::value;
    };

    template<>
    struct factorial<0> {
        static const uint64_t value = 1;
    };

    template<uint64_t alpha, uint64_t beta>
    struct monomial_2d {
        static const uint64_t value =
            factorial<alpha + beta + 2>::value /
            (factorial<alpha>::value * factorial<beta>::value);
    };
}