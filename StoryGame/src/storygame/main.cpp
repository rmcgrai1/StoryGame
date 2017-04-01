#include <complex>
#include <cstdlib>
#include <functional>
#include "resource\ResourceLocator.h"
#include "resource\manager\impl\GameManager.h"
#include "resource\graphics\impl\GraphicsGL.h"
#include "resource\log\impl\ConsoleLog.h"

IGraphicsWindow *mainWindow;

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

byte pixels[640 * 480 * 4];

void display(void) {
	ResourceLocator::get()->getManager()->tick();

	IGraphics *g = ResourceLocator::get()->getGraphics();
	g->getGraphicsSettings()->clear();

	glViewport(0, 0, 640, 480);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, -1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	IGraphicsPrimitive *gp = g->getGraphicsPrimitive();
	IGraphicsSettings *gs = g->getGraphicsSettings();
	IGraphics2D *g2d = g->getGraphics2D();

	/*glRotated(glfwGetTime()*360, 0, 0, -1);

	gp->color4d(1, 0, 0, 1);
	g2d->fillRectangle(0, 0, 640, 480);*/

	int i;
	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			// Draw noise.
			byte val = rand() % 255;

			// Draw mandelbrot set.
			//byte val = (byte)(getColor(x / 640., y / 480.) * 255);

			i = 4 * ((640 * y) + x);

			pixels[i] = val;
			pixels[i + 1] = val;
			pixels[i + 2] = val;
			pixels[i + 3] = 255;
		}
	}
	glDrawPixels(640, 480, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	frame.zoom(.8);
}


void pressFunction(int key) {
	if (key == GLFW_KEY_ESCAPE) {
		mainWindow->close();
	}
}

void releaseFunction(int key) {

}

int main(int argc, char **argv) {
	// Initialize ResourceLocator.
	ResourceLocator* rl = ResourceLocator::get();

	// Initialize Log.
	ILog *l = new ConsoleLog();
	rl->setLog(l);

	// Initialize Graphics.
	IGraphics *g = new GraphicsGL();
	rl->setGraphics(g);

	// Initialize Manager.
	IManager *m = new GameManager();
	rl->setManager(m);

	// Start.
	g->init();

	IGraphicsWindow* window = mainWindow = g->createGraphicsWindow();
	window->setTitle("Hello world!");
	window->setSize(640, 480);

	window->setTickFunc(display);
	window->setKeyboardPressFunc(pressFunction);
	window->setKeyboardReleaseFunc(releaseFunction);
	window->startLoop();

	glfwTerminate();

	return 0;
}