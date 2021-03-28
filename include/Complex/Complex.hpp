#pragma once
#include <cassert>
#include <cmath>
#include <fstream>
#include <initializer_list>
#include <iostream>

class Complex {
private:
    double _r, _i;

public:
    // Constructors, etc.
    Complex();						  // Constructor
    Complex(const double real, const double imag);	  // Constructor
    Complex(const std::initializer_list<double>& params); // Constructor
    Complex(const Complex& rhs);			  // Copy constructor
    Complex& operator=(const Complex& rhs);		  // Copy assignment
    Complex(Complex&& other);				  // Move constructor

    Complex& operator+=(const Complex& rhs);
    Complex& operator-=(const Complex& rhs);

    Complex& operator*=(const Complex& rhs);
    Complex& operator*=(const double& rhs);

    Complex& operator/=(const Complex& rhs);
    Complex& operator/=(const double& rhs);

    // Getters
    inline double real();
    inline double imag();
    inline double mod();
    inline double arg();
};

// Constructors, etc.
Complex::Complex()
{
    _r = 0.;
    _i = 0.;
}
Complex::Complex(const double real, const double imag)
{
    _r = real;
    _i = imag;
}
Complex::Complex(const Complex& rhs)
    : _r { rhs._r }
    , _i { rhs._i }
{
}
Complex::Complex(Complex&& rhs)
    : _r { rhs._r }
    , _i { rhs._i }
{
    rhs._r = 0.;
    rhs._i = 0.;
}
Complex& Complex::operator=(const Complex& rhs)
{
    if (this == &rhs)
	return *this;
    else {
	_r = rhs._r;
	_i = rhs._i;
    }
    return *this;
}

Complex& Complex::operator+=(const Complex& rhs)
{
    _r += rhs._r;
    _i += rhs._i;
    return *this;
}
Complex operator+(Complex lhs, const Complex& rhs)
{
    lhs += rhs;
    return lhs;
}
Complex operator+(Complex lhs, Complex& rhs)
{
    lhs += rhs;
    return lhs;
}
Complex& Complex::operator-=(const Complex& rhs)
{
    _r -= rhs._r;
    _i -= rhs._i;
    return *this;
}
Complex operator-(Complex lhs, const Complex& rhs)
{
    lhs -= rhs;
    return lhs;
}
Complex operator-(Complex lhs, Complex& rhs)
{
    lhs -= rhs;
    return lhs;
}

Complex& Complex::operator*=(const Complex& rhs)
{
    double r = (_r * rhs._r) - (_i * rhs._i);
    double i = (_r * rhs._i) + (_i * rhs._r);
    _r = r;
    _i = i;
    return *this;
}
Complex operator*(Complex lhs, const Complex& rhs)
{
    lhs *= rhs;
    return lhs;
}
Complex operator*(Complex lhs, Complex& rhs)
{
    lhs *= rhs;
    return lhs;
}
Complex& Complex::operator*=(const double& rhs)
{
    _r *= rhs;
    _i *= rhs;
    return *this;
}
Complex operator*(Complex lhs, const double& rhs)
{
    lhs *= rhs;
    return lhs;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    double denom = rhs._r * rhs._r + rhs._i * rhs._i;
    double r = (_r * rhs._r + _i * rhs._i) / denom;
    double i = (_i * rhs._r - _r * rhs._i) / denom;
    _r = r;
    _i = i;
    return *this;
}
Complex& Complex::operator/=(const double& rhs)
{
    _r /= rhs;
    _i /= rhs;
    return *this;
}
Complex operator/(Complex lhs, const Complex& rhs)
{
    lhs /= rhs;
    return lhs;
}
Complex operator/(Complex lhs, const double& rhs)
{
    lhs /= rhs;
    return lhs;
}

std::ostream&
operator<<(std::ostream& os, Complex& z)
{
    os << "(" << z.real() << ", " << z.imag() << ")";
    return os;
}

// Getters
inline double Complex::real()
{
    return _r;
}
inline double Complex::imag()
{
    return _i;
}
inline double Complex::mod()
{
    return sqrt(_r * _r + _i * _i);
}
inline double Complex::arg()
{
    return atan2(_i, _r);
}
