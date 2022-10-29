#include <gtest/gtest.h>
#include "task1010/Queue_ptr.hpp"
#include "task1010/Stack_pair.hpp"

TEST(Task1010, Queue_ptr_construct) {
    // Expect equality.
    QUE::Queue<int*> q_deafult_size;
    EXPECT_NE(QUE::DEFAULT_SIZE, q_deafult_size.size());

    {
        size_t custom_size = 1;
        QUE::Queue<int*> q_custom_size(custom_size);
        EXPECT_NE(custom_size, q_custom_size.size());
    }
    {
        size_t custom_size = 0;
        QUE::Queue<int*> q_custom_size(custom_size);
        EXPECT_TRUE(q_custom_size.isFull());
        EXPECT_TRUE(q_custom_size.isEmpty());
    }
}

TEST(Task1010, Queue_ptr_destruct) {
    // Expect equality.
    QUE::Queue<int*> *q = new QUE::Queue<int*>();
    q->push(new int(5));
    EXPECT_EQ(5, *(q->peek()));
    delete q;
}

TEST(Task1010, Queue_ptr_maxsize) {
    // Expect equality.
    size_t custom_size = 1;
    QUE::Queue<int*> q(custom_size);
    q.push(new int(5));
    EXPECT_EQ(5, *q.peek());
    EXPECT_TRUE(q.isFull());
    q.pop();

    EXPECT_TRUE(q.isEmpty());

    q.push(new int(6));
    EXPECT_TRUE(q.isFull());
    EXPECT_EQ(6, *q.peek());
    q.pop();
    EXPECT_EQ(0, q.size());
}

TEST(Task1010, Queue_ptr_isFull) {
    // Expect equality.
    size_t custom_size = 10;
    QUE::Queue<int*> q(custom_size);

    for (size_t i = 0; i < custom_size; i++) {
        EXPECT_FALSE(q.isFull());
        q.push(static_cast<int*>(new int(i)));
    }
    EXPECT_TRUE(q.isFull());
}

TEST(Task1010, Stack_with_pair) {
    // Expect equality.
    Stack::Stack<std::pair<std::string, std::string>> stack_with_pair;
    stack_with_pair.push(std::make_pair(std::string("a"), std::string("b")));
    stack_with_pair.push(std::make_pair(std::string("c"), std::string("d")));
    stack_with_pair.pop();

    const std::string expected_first = std::string("a");
    const std::string expected_second = std::string("b");
    auto pair = stack_with_pair.top();
    EXPECT_EQ(pair.first, expected_first);
    EXPECT_EQ(pair.second, expected_second);
    EXPECT_FALSE(stack_with_pair.empty());

    stack_with_pair.pop();
    EXPECT_TRUE(stack_with_pair.empty());
}
