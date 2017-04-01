#include "resource\ResourceLocator.h"
#include "resource\manager\impl\GameManager.h"
#include "resource\graphics\impl\GraphicsGL.h"
#include "resource\log\impl\ConsoleLog.h"

IGraphicsWindow *mainWindow;

void display(void) {
	ResourceLocator::get()->getManager()->tick();
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