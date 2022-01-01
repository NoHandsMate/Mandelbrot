#ifndef MANDEL_H
#define MANDEL_H

#include "EasyBMP.h"
#include <complex>
#include <iostream>
#include <utility>
#include <cassert>
#include <chrono>

constexpr int MAX_ITER{ 256 };
constexpr int WIDTH{ 800 };
constexpr int HEIGHT{ 600 };

constexpr float RE_START{ -2 };
constexpr float RE_END{ 1 };
constexpr float IM_START{ -1 };
constexpr float IM_END{ 1 };

auto mandelbrot(const std::complex<float>& complex) {
	std::complex<float> z{};
	int n{ 0 };

	while (std::abs(z) <= 2 && n < MAX_ITER) {
		z = (z * z) + complex;
		n++;
	}

	return n;
}

// Linear mapping from pixel range to specified complex range
template<typename T>
auto coord_to_complex(const std::pair<T, T>& pixel_range, const std::pair<T, T>& complex_range, T value) -> T {
	T value_norm = value - pixel_range.first;
	T pixel_range_norm = pixel_range.second - pixel_range.first;
	T normPosition = value_norm / pixel_range_norm;

	T complex_range_norm = complex_range.second - complex_range.first;
	T outNorm = normPosition * complex_range_norm;
	T outVal = complex_range.first + outNorm;

	return outVal;
}


auto hsv_to_rgb(int hue, int saturation, int value) -> EasyBMP::RGBColor {

	assert(hue >= 0 && hue <= 360 || saturation >= 0 && saturation <= 1 || value >= 0 && value <= 1, "Value are not in range");

	auto func = [&](int n) {
		auto k = (n + hue / 60) % 6;
		auto temp_min = std::min(k, 4 - k);
		return value - (value * saturation * std::max(0, std::min(temp_min, 1)));
	};

	return EasyBMP::RGBColor(func(5), func(3), func(1));
}

#endif