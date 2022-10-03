#include <iostream>
#include "part1.hpp"

int main()
{
 /* 
   *    Part 1
    */
	std::cout << "\ntask1\n";
    auto m1 = part1::Matrix<double>(2, 2);
    auto m2 = part1::Matrix<double>(2, 2);
    m1 += m2;

    char s1[10] = "hello";
    char s2[10] = "world";
    std::cout << part1::sum(s1, s2);

	return 0;
}
