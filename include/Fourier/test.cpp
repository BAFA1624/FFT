#include "../Complex/Complex.hpp"
#include <iostream>
#include <vector>

template <typename T>
std::pair<bool, size_t> sizeCheck(const std::vector<T>& arr)
{
    double n = (double)arr.size();
    size_t power_2 = 2;
    while (n >= 2) {
	if (n == 2.) {
	    return { true, 0 };
	}
	n /= 2;
	power_2 *= 2;
    }
    return { false, power_2 * 2 };
}

int main()
{
    Complex a(1, 0), b(6.12323e-17, 1);
    a *= b;
    std::cout << a << std::endl;
}
