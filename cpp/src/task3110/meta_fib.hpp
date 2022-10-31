#pragma once

#include "meta_vector.hpp"

namespace meta_fib {
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

    template <int64_t n> struct fibon {
        typedef typename meta_vector::push_back< typename fibon<n-1>::type , Fibonachi<n-1>::value >::type type;
    };

    template <> struct fibon<0> {
        typedef meta_vector::meta_vector<> type;
    };
}

