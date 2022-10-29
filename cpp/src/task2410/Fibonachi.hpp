#pragma once

#include <boost/multiprecision/cpp_int.hpp>

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

    template<size_t INDEX>
    struct LongFibonachi {
        static constexpr boost::multiprecision::uint1024_t value = 
            LongFibonachi<INDEX - 1>::value + LongFibonachi<INDEX - 2>::value;
    };

    template<>
    struct LongFibonachi<1> {
        static constexpr boost::multiprecision::uint1024_t value = 1;
    };

    template<>
    struct LongFibonachi<0> {
        static constexpr boost::multiprecision::uint1024_t value = 0;
    };
}
