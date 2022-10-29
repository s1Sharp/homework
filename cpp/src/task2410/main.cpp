#include <iostream>
#include <string>
#include "Fibonachi.hpp"
#include "monomial_2d.hpp"

int main()
{
/*
  *   Part 1
   */

    std::cout << Fibonachi::Fibonachi<10>::value << std::endl;

/*
  *   Part 2
   */

    const double mon_2d_integral_1_1 = 1. / Factorial::monomial_2d<4, 4>::value;
    std::cout << "monomial_2d integral: " << mon_2d_integral_1_1 << std::endl;

    const double mon_2d_integral_2_3 = 1. / Factorial::monomial_2d<1, 4>::value;
    std::cout << "monomial_2d integral: " << mon_2d_integral_2_3 << std::endl;

    return 0;
}
