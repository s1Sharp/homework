#pragma once

#include <type_traits>
#include "meta_pow.hpp"
#include "monomial_2d.hpp"

namespace meta_loop {
    using namespace meta_p;
    using namespace Factorial;

    template<unsigned N, unsigned K> struct C {
        static const unsigned value =
                factorial<N>::value / factorial<K>::value / factorial<N-K>::value;
    };

    template<unsigned N, unsigned I, class Closure>
    typename std::enable_if<(I == N)>::type meta_loop0(Closure& closure)
    {}

    template<unsigned N, unsigned I, class Closure>
    typename std::enable_if<(I < N)>::type meta_loop0(Closure& closure)
    {
        closure.template apply<I>();
        meta_loop0<N, I + 1>(closure);
    }

    template<unsigned N, class Closure>
    void meta_loop(Closure& closure) {
        meta_loop0<N, 0>(closure);
    }

    template<class Closure>
    struct abstract_sum_closure
    {
        typedef typename
        Closure::value_type value_type;
        abstract_sum_closure(Closure& closure) : closure(closure), result(value_type()) 
        {}

        template<unsigned I>
        void apply() {
            result += closure.template
            value<I>();
        }

        Closure& closure;
        value_type result;
    };

    template<unsigned N, class Closure>
    typename Closure::value_type abstract_sum(Closure& closure)
    {
        abstract_sum_closure<Closure> my_closure(closure);
        meta_loop<N>(my_closure);
        return my_closure.result;
    }

    template<unsigned N, typename T>
    struct binom_closure
    {
        typedef T value_type;
        // using value_type = T;
        binom_closure(value_type a, value_type b) : a(a), b(b) 
        {}

        template<unsigned K>
        value_type value() const {
            return ( C<N, K>::value * meta_pow<K>(a) * meta_pow<N-K>(b) / monomial_2d<K, N - K>::value);
        }

        private:
        const value_type a, b;
    };
}

namespace meta_binom {

    template<unsigned N, typename T>
    T binom(T a, T b)
    {
        meta_loop::binom_closure<N, T> closure(a, b);
        return meta_loop::abstract_sum<N + 1>(closure);
    }

}