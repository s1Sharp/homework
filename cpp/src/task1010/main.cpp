#include <iostream>
#include <string>
#include "Queue_ptr.hpp"
#include "Stack.hpp"
#include "Stack_pair.hpp"

int main()
{
 /* 
   *    Part 1
    */

    QUE::Queue<std::string*> q(4);
    
    q.push(new std::string("a"));

    std::cout << "The front ptr to element is " << q.peek() << std::endl;
    std::cout << "The front element is " << *q.peek() << std::endl;
    q.pop();

    q.push(new std::string("b"));

    std::cout << "The queue size is " << q.size() << std::endl;
    q.pop();

    if (q.isEmpty()) {
        std::cout << "The queue is empty\n";
    }
    else {
        std::cout << "The queue is not empty\n";
    }

 /* 
   *    Part 2
    */

    Stack::Stack<std::string> stack;
    stack.push(std::string("a"));
    std::cout << "The top value: " << stack.top() << std::endl;
    stack.push(std::string("b"));

    std::cout << "The full stack: " << stack << std::endl;

    stack.pop();
    std::cout << "The full stack after pop: " << stack << std::endl;

 /* 
   *    Part 3
    */

    Stack::Stack<std::pair<std::string, std::string>> stack_with_pair;
    stack_with_pair.push(std::make_pair(std::string("a"), std::string("b")));
    stack_with_pair.push(std::make_pair(std::string("c"), std::string("d")));

    std::cout << "The full pair stack: " << stack_with_pair << std::endl;

    stack_with_pair.pop();
    std::cout << "The full pair stack after pop: " << stack_with_pair << std::endl;

	return 0;
}
