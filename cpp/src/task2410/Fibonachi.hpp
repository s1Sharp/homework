#pragma once

#include <stdint.h>

namespace Fibonachi {
    template<size_t INDEX>
    struct Fibonachi {
        static constexpr uint64_t value = 
            Fibonachi<INDEX - 1>::value + Fibonachi<INDEX - 2>::value;
    };

    template<>
    struct Fibonachi<1> {
        static constexpr uint64_t value = 1;
    };

    template<>
    struct Fibonachi<0> {
        static constexpr uint64_t value = 0;
    };
}
