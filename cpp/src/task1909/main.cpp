#include <iostream>
#include "part1.hpp"


int main()
{
 /* 
   *    Part 1
    */
	std::cout << "\ntask1\n";
    auto m = part1::Matrix<double>(3, 3);
    std::cout << m.det() << std::endl;
    std::cout << part1::modul(m) << std::endl;

    auto c = part1::Complex(122, 344);
    std::cout << c.det() << std::endl;
    std::cout << part1::modul(c) << std::endl;

	return 0;
}