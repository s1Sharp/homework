#pragma once

#include <utility>
#include "Stack.hpp"

namespace Stack{
    template <typename T>
    class Stack <std::pair<T, T>> {
    private:
        std::vector<std::pair<T, T>> v;
    public:
        void push(std::pair<T, T> const&e);
        void pop();
        std::pair<T, T> const& top() const;
        bool empty() const {
            return v.empty();
        }
        std::pair<T, T> new_pop();
        void printOn(std::ostream& os) const {
            for(std::pair<T, T> const& el : v) {
                os << "(" << el.first << ", " << el.second << "), ";
            }
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, Stack<std::pair<U, U>> const&s);
    };

    template <typename T>
    void Stack<std::pair<T, T>>::push(std::pair<T, T> const&e) {
        v.push_back(e);
    }

    template <typename T>
    void Stack<std::pair<T, T>>::pop(){
        assert(!v.empty());
        v.pop_back();
    }

    template <typename T>
    std::pair<T, T> const& Stack<std::pair<T, T>>::top() const {
        assert(!v.empty());
        return v.back();
    }

    template <typename T>
    std::pair<T, T> Stack<std::pair<T, T>>::new_pop() {
        assert(!v.empty());
        std::pair<T, T> e = v.back();
        v.pop_back();
        return e;
    };

    template<typename U>
    std::ostream& operator<<(std::ostream& os, Stack<std::pair<U, U>> const&s) {
        for(const std::pair<U, U>& el: s.v)
            os << "(" << el.first << ", " << el.second << "), ";
        return os;
    }
}