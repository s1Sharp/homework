#include <iostream>
#include <string>
#include "Queue.hpp"

int main()
{
 /* 
   *    Part 1
    */
    QUE::Queue<std::string> q(4);

    q.push("a");
    q.push("b");
    q.push("c");

    std::cout << "The front element is " << q.peek() << std::endl;
    q.pop();

    q.push("d");

    std::cout << "The queue size is " << q.size() << std::endl;

    q.pop();
    q.pop();
    q.pop();

    if (q.isEmpty()) {
        std::cout << "The queue is empty\n";
    }
    else {
        std::cout << "The queue is not empty\n";
    }

	return 0;
}
