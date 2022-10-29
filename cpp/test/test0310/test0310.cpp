#include <gtest/gtest.h>
#include "task0310/Queue.hpp"

TEST(Task0310, Queue_construct) {
    // Expect equality.
    QUE::Queue<int> q_deafult_size;
    EXPECT_NE(QUE::DEFAULT_SIZE, q_deafult_size.size());

    {
        size_t custom_size = 1;
        QUE::Queue<int> q_custom_size(custom_size);
        EXPECT_NE(custom_size, q_custom_size.size());
    }
    {
        size_t custom_size = 0;
        QUE::Queue<int> q_custom_size(custom_size);
        EXPECT_TRUE(q_custom_size.isFull());
        EXPECT_TRUE(q_custom_size.isEmpty());
    }
}

TEST(Task0310, Queue_destruct) {
    // Expect equality.
    QUE::Queue<int>* q = new QUE::Queue<int>();
    q->push(5);
    EXPECT_EQ(5, q->peek());
    delete q;
}

TEST(Task0310, Queue_maxsize) {
    // Expect equality.
    size_t custom_size = 1;
    QUE::Queue<int> q(custom_size);
    q.push(5);
    EXPECT_EQ(5, q.peek());
    EXPECT_TRUE(q.isFull());
    q.pop();

    EXPECT_TRUE(q.isEmpty());

    q.push(6);
    EXPECT_TRUE(q.isFull());
    EXPECT_EQ(6, q.peek());
    q.pop();
    EXPECT_EQ(0, q.size());
}

TEST(Task0310, Queue_isFull) {
    // Expect equality.
    size_t custom_size = 10;
    QUE::Queue<int> q(custom_size);

    for (size_t i = 0; i < custom_size; i++) {
        EXPECT_FALSE(q.isFull());
        q.push(static_cast<int>(i));
    }
    EXPECT_TRUE(q.isFull());
}