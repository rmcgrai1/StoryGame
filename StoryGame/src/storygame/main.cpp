#include <cstdlib>
#include "resource\ResourceLocator.h"
#include "resource\manager\impl\GameManager.h"
#include "resource\graphics\impl\GraphicsGL.h"
#include "resource\log\impl\ConsoleLog.h"
#include "minigame\Tetris.h"

IGraphicsWindow *mainWindow;
Tetris *tetris = new Tetris();

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

	/*IGraphicsPrimitive *gp = g->getGraphicsPrimitive();
	IGraphicsSettings *gs = g->getGraphicsSettings();
	IGraphics2D *g2d = g->getGraphics2D();

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
	glDrawPixels(640, 480, GL_RGBA, GL_UNSIGNED_BYTE, pixels);*/

	tetris->tick();
	tetris->draw();
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