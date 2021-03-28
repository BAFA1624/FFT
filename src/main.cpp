#include "../include/Complex/Complex.hpp"
#include "../include/Fourier/fft-recursive.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

void _fft(std::vector<Complex>::iterator buf, std::vector<Complex>::iterator out, size_t n, size_t step)
{
    if (step < n) {
	// std::cout << "n = " << n << ". Val of step = " << step << ". Val of step * 2 = " << step * 2 << "." << std::endl;
	_fft(out, buf, n, step * 2);
	_fft(out + step, buf + step, n, step * 2);

	for (size_t i = 0; i < n; i += 2 * step) {
	    Complex t(cos(M_PI * i / n), sin(M_PI * i / n));
	    t *= out[i + step];
	    //  if (out[i + step].real() == 0. && out[i + step].imag() == 0)
	    //	std::cout << "out[...] = " << out[i + step] << ", t = " << t << std::endl;
	    buf[i / 2] = out[i] + t;
	    buf[(i + n) / 2] = out[i] - t;
	}
    }
}

void fft(std::vector<Complex>& buf)
{
    size_t n = buf.size();
    std::vector<Complex> out(n);
    for (size_t i = 0; i < n; i++)
	out[i] = buf[i];
    _fft(buf.begin(), out.begin(), n, 1);
}

void ifft(std::vector<Complex>& buf)
{
    size_t n = buf.size();
    std::vector<Complex>
	out(n);
    for (size_t i = 0; i < n; i++)
	out[i] = buf[i];
    _fft(buf.begin(), out.begin(), n, 1);

    for (size_t i = 0; i < n; i++)
	buf[i] = buf[i] * (1. / n);
}
Complex h1(double t)
{
    Complex result(cos(t) + cos(5 * t), sin(t) + sin(5 * t));
    return result;
}

// Discrete Fourier Transform taking array of samples
std::vector<Complex> DFT(const std::vector<Complex>& samples)
{
    size_t N = samples.size();

    // Alloc memory for resulting array & declare vars
    std::vector<Complex> arr(N);

    // H_n & h_k keep track of which values are currently in use
    // theta stores value of exponent h_k(t_k).exp(-2.pi.n.k/N) for use in Euler's formula
    Complex H_n, h_k, tmp;
    double theta;
    size_t n, k;

    // For every values H_n, sum contributions of all h_k then add to resulting array
    for (n = 0; n < N; n++) {
	// initialize H_n
	Complex H_n(0., 0.);

	for (k = 0; k < N; k++) {
	    // Calculate exponent of h_k(t_k).exp(-2.pi.n.k/N)
	    theta = 2. * M_PI * n * k / N;
	    h_k = samples[k];

	    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
	    // h_k(t_k).exp(-2.pi.n.k/N):
	    Complex tmp(h_k.real() * cos(theta) + h_k.imag() * sin(theta), h_k.imag() * cos(theta) - h_k.real() * sin(theta));
	    // H_n.r += (h_k.real() * cos(theta) + h_k.imag() * sin(theta));
	    // H_n.i += (h_k.imag() * cos(theta) - h_k.real() * sin(theta));
	    H_n += tmp;
	}

	arr[n] = H_n;
    }

    return arr;
}

int main()
{
    /*
    size_t N = 128;
    std::vector<Complex> h_1(N);
    std::vector<Complex> h_2(N);
    auto it = h_2.begin();
    double t = 0.;
    double dt = 2. * M_PI / N;
    FILE* fp1 = fopen("h.txt", "w");
    if (!fp1)
	exit(-2);

    fprintf(fp1, "time,real,imag\n");
    for (auto& z : h_1) {
	z = h1(t);
	*it = z;
	it++;
	fprintf(fp1, "%lf,%lf,%lf\n", t, z.real(), z.imag());
	t += dt;
    }

    fclose(fp1);

    auto DFT_test = DFT(h_1);

    fft(h_1);
    std::vector<Complex> H2 = fft_recursive(h_2);
    std::cout << "Results of fft_recursive:\n";
    for (auto& z : H2)
	std::cout << z << '\t';
    putchar('\n');

    ifft(DFT_test);

    FILE* fp2 = fopen("results.txt", "w");
    if (!fp2)
	exit(-2);

    t = 0.;
    fprintf(fp2, "time,real,imag\n");
    for (auto& z : DFT_test) {
	fprintf(fp2, "%lf,%lf,%lf\n", t, z.real(), z.imag());
	t += dt;
    }

    fclose(fp2);*/

    double t = 0.;
    double dt = 2. * M_PI / 100;
    std::vector<Complex> h(100);
    for (auto& z : h) {
	z = h1(t);
	t += dt;
    }

    Complex zeroes(0., 0.);
    h.resize(128, zeroes);

    std::vector<Complex> H = DFT(h);

    std::vector<Complex> ih = DFT(H);
    for (size_t i = 0; i < 128; ++i) {
	ih[i] /= 100;
	std::cout << h[i] << ", " << ih[i] << std::endl;
    }
}
