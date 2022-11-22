#include <iostream>
#include <string>
#include "meta_fib.hpp"
#include "meta_pow.hpp"

int main()
{
 /* 
   *    Part 1
    */
	typedef meta_fib::fibon<10>::type f;
	f a;
    //std::cout << "The full pair stack after pop: " << stack_with_pair << std::endl;

 /* 
   *    Part 2
    */
    std::cout << meta_p::meta_pow<5>(2.2);

	return 0;
}
