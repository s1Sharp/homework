#pragma once

#include <iostream>
#include <vector>
#include <cassert>

namespace Stack{
    template <typename T>
    class Stack{
    private:
        std::vector<T> v;
    public:
        void push(T const&e);
        void pop();
        T const& top() const;
        bool empty() const {
            return v.empty();
        }
        T new_pop();
        void printOn(std::ostream& os) const {
            for(T const& el : v) {
                os << el << ' ';
            }
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, Stack<U> const&s);
    };

    template <typename T>
    void Stack<T>::push(T const&e) {
        v.push_back(e);
    }

    template <typename T>
    void Stack<T>::pop(){
        assert(!v.empty());
        v.pop_back();
    }

    template <typename T>
    T const& Stack<T>::top() const {
        assert(!v.empty());
        return v.back();
    }

    template <typename T>
    T Stack<T>::new_pop() {
        assert(!v.empty());
        T e = v.back();
        v.pop_back();
        return e;
    };

    template<typename U>
    std::ostream& operator<<(std::ostream& os, Stack<U> const&s) {
        for(auto a: s.v)
            os << a <<' ';
        return os;
    }
}