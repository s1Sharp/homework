#pragma once

#include <type_traits>
#include <stdint.h>

namespace meta_p {
    template <int N, typename T>
    typename std::enable_if<(N < 0), T>::type meta_pow(T x) {
        return (1 / meta_pow<-N>(x));
    }

    template <int N, typename T>
    typename std::enable_if<(N == 0), T>::type meta_pow(T x) {
        return (1);
    }

    template <int N, typename T>
    typename std::enable_if<(N == 1), T>::type meta_pow(T x) {
        return (x);
    }

    template <int N, typename T>
    typename std::enable_if<(N > 0) && (N % 2 == 1), T>::type meta_pow(T x) {
        return (meta_pow< N - 1 >(x) * x);
    }

    template <int N, typename T>
    typename std::enable_if<(N > 0) && (N % 2 == 0), T>::type meta_pow(T x) {
        T p = meta_pow< (N / 2) >(x);
        return (p * p);
    }
};

