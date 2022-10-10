#pragma once

#include <type_traits>
#include <iostream>
#include <cstdlib>

namespace QUE {
    using namespace std;

    // Define the default capacity of the queue
    static const size_t DEFAULT_SIZE = 100;

    // A class to represent a queue
    template <class X>
    class Queue {
        X *arr;             // array to store queue elements
        size_t capacity;    // maximum capacity of the queue
        int front;          // front points to the front element in the queue (if any)
        int back;           // back points to the last element in the queue
        size_t count;       // current size of the queue

    public:
        Queue(size_t size = DEFAULT_SIZE);     // constructor
        ~Queue();
        void pop();
        void push(X x);
        X peek();
        size_t size();
        bool isEmpty();
        bool isFull();
    };

    // Constructor to initialize a queue
    template <class X>
    Queue<X>::Queue(size_t size) {
        arr = new X[size];
        capacity = size;
        front = 0;
        back = -1;
        count = 0;
    }

    // Destructor
    template <class X>
    Queue<X>::~Queue() {
        delete []arr;
        arr = nullptr;
        capacity = 0;
        front = 0;
        back = 0;
        count = 0;
    }

    // Utility function to dequeue the front element
    template <class X>
    void Queue<X>::pop() {
        // check for queue underflow
        if (isEmpty()) {
            cout << "Underflow\nProgram Terminated\n";
            exit(EXIT_FAILURE);
        }

        cout << "Removing " << arr[front] << endl;

        front = (front + 1) % capacity;
        count--;
    }

    // Utility function to add an item to the queue
    template <class X>
    void Queue<X>::push(X item) {
        // check for queue overflow
        if (isFull()) {
            cout << "Overflow\nProgram Terminated\n";
            exit(EXIT_FAILURE);
        }

        cout << "Inserting " << item << endl;
    
        back = (back + 1) % capacity;
        arr[back] = item;
        count++;
    }

    // Utility function to return the front element of the queue
    template <class X>
    X Queue<X>::peek() {
        if (isEmpty())
        {
            cout << "UnderFlow\nProgram Terminated\n";
            exit(EXIT_FAILURE);
        }
        return arr[front];
    }

    // Utility function to return the size of the queue
    template <class X>
    size_t Queue<X>::size() {
        return static_cast<size_t>(count);
    }

    // Utility function to check if the queue is empty or not
    template <class X>
    bool Queue<X>::isEmpty() {
        return (size() == 0);
    }

    // Utility function to check if the queue is full or not
    template <class X>
    bool Queue<X>::isFull() {
        return (size() == capacity);
    }
}
