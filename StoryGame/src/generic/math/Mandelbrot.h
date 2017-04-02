#pragma once

#include <math.h>

template <typename T>
class window {
	public:
	T _x_min, _x_max, _y_min, _y_max;

	window(T x_min, T x_max, T y_min, T y_max)
		: _x_min(x_min), _x_max(x_max), _y_min(y_min), _y_max(y_max) {}
	// Utility functions for getting the size, width and height of the window
	T size() {
		return (width() * height());
	}
	T width() {
		return (_x_max - _x_min);
	}
	T height() {
		return (_y_max - _y_min);
	}

	void zoom(double frac) {
		_x_min = xc + (_x_min - xc) * frac;
		_x_max = xc + (_x_max - xc) * frac;
		_y_min = yc + (_y_min - yc) * frac;
		_y_max = yc + (_y_max - yc) * frac;
	}
};

// Mandelbrot functions.
//window<double> frame(-2.2, 1.2, -1.7, 1.7);
double xc = -1.75, yc = 0;
window<double> frame(xc + -1, xc + 1, yc + -1, yc + 1);

int iterMax = 500;
double getColor(double xf, double yf) {
	double
		cr = xf * frame.width() + frame._x_min,
		ci = yf * frame.height() + frame._y_min,
		zr = 0,
		zi = 0;

	double zr2, zi2, zrf, zif;
	int iter;
	for (iter = 0; iter < iterMax; iter++) {
		zr2 = zr*zr;
		zi2 = zi*zi;

		if (sqrt(zr2 + zi2) >= 2) {
			break;
		}

		zrf = (zr2 - zi2) + cr;
		zif = (2 * zr*zi) + ci;

		zr = zrf;
		zi = zif;

		iter++;
	}

	return (1.*iter / iterMax);
}