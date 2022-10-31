#pragma once

#include <stdint.h>

namespace meta_vector {
    using vector_type = uint64_t;
    
    template <vector_type... I> struct meta_vector {};
    template <class MetaVector, vector_type i> struct push_back;

    template <vector_type... I, vector_type i>
    struct push_back<meta_vector<I...>, i> {
        using type = meta_vector<I..., i>;
    };

    template <class MetaVector, size_t n> struct at;

    template <vector_type i, vector_type... I, size_t n>
    struct at<meta_vector<i, I...>, n> : at<meta_vector<I...>, n - 1> {};

    template <vector_type i, vector_type... I>
    struct at<meta_vector<i, I...>, 0> : std::integral_constant<int, i> {};
}

