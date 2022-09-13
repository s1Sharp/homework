#include <iostream>
#include "part1.hpp"
#include "part2.hpp"

int main()
{
 /* 
   *    Part 1
    */
	std::cout << "\ntask1\n";
    std::cout << part1::min<double>(8.1, 5.3) << std::endl;
    std::cout << part1::min(8.1f, 5.3f) << std::endl;  // template type will auto defined as float
    std::cout << part1::min<double>(8.1f, 5) << std::endl;  // will cast float and int to double type

    std::cout << part1::max<double>(8.1, 5.3) << std::endl;
    std::cout << part1::max(8.1f, 5.3f) << std::endl;  // template type will auto defined as float
    std::cout << part1::max<double>(8.1, 5.f) << std::endl;  // will cast float and int to double type


    float t1 = 8.1f;
    float t2 = 5.3f;

    std::cout<< "before swap\nt1 = " << t1 << "\nt2 = " << t2 << std::endl;
    part1::swap(t1, t2);  // swap by reference
    std::cout<< "after swap\nt1 = " << t1 << "\nt2 = " << t2 << std::endl;

 /* 
   *    Part 2
    */
	std::cout << "\ntask2\n";
    std::array<int8_t, 5> Array = { 2, 3, 4, 5, 6};
    part2::iter(Array.data(), Array.size(), part2::custom_increment_print<int8_t>);

	return 0;
}