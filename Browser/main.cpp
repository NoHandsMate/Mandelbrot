#include "Mandelbrot.h"

auto main() -> int {

	EasyBMP::Image image(WIDTH, HEIGHT, "mandel.bmp", EasyBMP::RGBColor(0, 0, 0));

	// RE_a and IM_a refers to the (x,y) pixel position
	// RE_b and IM_b refers to the inteval where this positions need to be mapped
	std::pair<float, float> RE_a(0, WIDTH);
	std::pair<float, float> RE_b(RE_START, RE_END);
	std::pair<float, float> IM_a(0, HEIGHT);
	std::pair<float, float> IM_b(IM_START, IM_END);

	auto start = std::chrono::steady_clock::now();

	for (float x = 0; x < WIDTH; ++x) {
		for (float y = 0; y < HEIGHT; ++y) {
			
			auto real_mapping = coord_to_complex(RE_a, RE_b, x);
			auto imaginary_mapping = coord_to_complex(IM_a, IM_b, y);
			
			std::complex<float> c(real_mapping, imaginary_mapping);
			auto iter = mandelbrot(c);
			
			auto hue = (iter * 255 / MAX_ITER);
			auto saturation = 255;
			auto value = (iter < MAX_ITER) ? 255 : 0;

			auto color = hsv_to_rgb(hue, saturation, iter);
			image.SetPixel(x, y, color);
		}
	}
	
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> time = end - start;

	image.Write();

	std::cout << "TIME: " << time.count();
}