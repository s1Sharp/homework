#include <iostream>
#include "part1.hpp"

int main()
{
	std::cout << "task1\n";
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

	return 0;
}