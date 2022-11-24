#include <iostream>
#include <string>
#include "meta_loop.hpp"

int main()
{
 /* 
   *    Part 1
    */
    constexpr unsigned N1 = 2;
    constexpr double a1 = 2, b1 = 2;
    const double bi1 = meta_binom::binom<N1>(a1, b1); // вычисление интеграла
    std::cout << bi1 << '\n';

	constexpr double a2 = 1.2, b2 = 3.4;
	constexpr unsigned N2 = 5;
	const double bi2 = meta_binom::binom<N2>(a2, b2);
    std::cout << bi2 << '\n';

    return 0;
}
