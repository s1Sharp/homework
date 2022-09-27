#include <iostream>
#include "part1.hpp"
#include "part2.hpp"

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

 /* 
   *    Part 2
    */
	std::cout << "\ntask2\n";

    std::vector<int>input1 = {4, 90, 0};
    std::vector<int>output1 = {0, 4, 90};
    part2::custom_sort(input1);

    std::cout << "RadixSort correct = " << (input1 == output1) << std::endl;

    std::vector<double>input2 = {4., 90., 0.};
    std::vector<double>output2 = {0., 4., 90.};
    part2::custom_sort(input2);
    std::cout << "Standart double sort correct = " << (input2 == output2) << std::endl;

    std::vector<float>input3 = {4.f, 90.f, 0.f};
    std::vector<float>output3 = {0.f, 4.f, 90.f};
    part2::custom_sort(input3);
    std::cout << "Standart float sort correct = " << (input3 == output3) << std::endl;


    std::cout << "Template factorial correct = " << (120 == part2::Factorial<5>::value) << std::endl;

	return 0;
}