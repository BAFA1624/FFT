#pragma once
#include <cmath>

class Complex {
private:
    double _r, _i;

public:
    // Constructors, etc.
    Complex();
    Complex(double real, double imag);
    Complex(Complex&& other);

    // Operators
    Complex& operator=(const Complex& other);

    // Getters
    inline double real();
    inline double imag();
    inline double mod();
    inline double arg();
};
