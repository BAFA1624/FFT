#pragma once
#include "../Complex/Complex.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <new>
#include <vector>

template <typename T>
std::vector<T> vector_slice(const std::vector<T>& arr, const long start, const long stop, const long stride)
{
    const long len = (long)arr.size();
    // Checks to ensure slice parameters (start, stop, & stride) are valid
    // Assert throw error if they aren't met
    bool valid_stride, valid_start, valid_stop;
    if (start <= stop) { // Checks for slices moving in +ve direction
	valid_stride = (stride > 0);
	valid_start = (start >= 0);
	valid_stop = (stop <= len);
    } else { // Checks for slices moving in the -ve direction
	valid_stride = (stride < 0);
	valid_start = (start <= len);
	valid_stop = (stop >= 0);
    }
    /*std::cout << "\nvalid_stride = " << valid_stride << std::endl;
    std::cout << "valid_start = " << valid_start << std::endl;
    std::cout << "valid_stop = " << valid_stop << std::endl;*/
    assert(valid_stride && valid_start && valid_stop);

    long i;
    std::vector<T> result;

    if (start <= stop) {
	// std::cout << "A: start = " << start << ", stop = " << stop << ", stride = " << stride << std::endl;
	for (i = start; i < stop + 1; i += stride) {
	    result.push_back(arr[i]);
	}
	return result;
    } else {
	// std::cout << "B: start = " << start << ", stop = " << stop << ", stride = " << stride << std::endl;
	for (i = start; i > stop - 1; i += stride) {
	    result.push_back(arr[i]);
	}
	return result;
    }
}

// Checks if provided array's size is a power of 2
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
    return { false, power_2 * 4 };
}

std::vector<Complex> fft_recursive(std::vector<Complex>& a)
{
    size_t n = a.size();
    if (n == 1) {
	return a;
    }

    // Checking size of vector is power of 2.
    // If not, resize to next power of 2,
    // initialize new vals as (0 + 0i).
    size_t ini_sz = a.size();
    std::pair<bool, size_t> a_sz_check = sizeCheck(a);
    if (!a_sz_check.first) {
	Complex val(0., 0.);
	a.resize(a_sz_check.second, val);
	n = a_sz_check.second;
    }

    Complex omega(1, 0), omega_n(cos(2 * M_PI / n), sin(2 * M_PI / n));

    std::vector<Complex> a_even = vector_slice(a, 0, n - 2, 2);
    std::vector<Complex> a_odd = vector_slice(a, 1, n - 1, 2);

    std::vector<Complex> y_even = fft_recursive(a_even);
    std::vector<Complex> y_odd = fft_recursive(a_odd);

    if (y_even.size() == 1 && y_odd.size() == 1)
	std::cout << "y_even.size() & y_odd.size() == 1. y_even[0] = " << y_even[0] << ", y_odd[0] = " << y_odd[0] << std::endl;
    else if (y_even.size() == 1)
	std::cout << "y_even.size() == 1. y_even[0] = " << y_even[0] << std::endl;
    else if (y_odd.size() == 1)
	std::cout << "y_odd.size() == 1. y_odd[0] = " << y_even[0] << std::endl;

    std::vector<Complex> result(n);

    for (size_t k = 0; k < n / 2 - 1; ++k) {
	std::cout << "y_even[" << k << "] = " << y_even[k] << ", omega = " << omega << ", y_odd[" << k << "] = " << y_odd[k] << std::endl;
	result[k] = y_even[k] + omega * y_odd[k];
	result[k + (n / 2)] = y_even[k] - omega * y_odd[k];
	omega = omega * omega_n;
    }

    if (!a_sz_check.first) {
	// a was resized at the start, revert to original size
	a.resize(ini_sz);
	result.resize(ini_sz);
    }

    return result;
}
