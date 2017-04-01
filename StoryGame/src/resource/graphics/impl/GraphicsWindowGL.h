#pragma once

#include <thread>
#include <GLFW/glfw3.h>
#include "../IGraphicsWindow.h"

// TODO: Find a solution to get these into the class.
void(*pressCallback)(int) = nullptr;
void(*releaseCallback)(int) = nullptr;
void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (pressCallback != nullptr) {
			pressCallback(key);
		}
	} else if (action == GLFW_RELEASE) {
		if (releaseCallback != nullptr) {
			releaseCallback(key);
		}
	}
}

// TODO: Friend function??????
class GraphicsWindowGL;
void loop(GraphicsWindowGL *window);

class GraphicsWindowGL : public IGraphicsWindow {
	public:
	GraphicsWindowGL() {
		window = glfwCreateWindow(300, 300, "", NULL, NULL);
	}
	void setTitle(string title) {
		glfwSetWindowTitle(window, title.c_str());
	};
	void setSize(int width, int height) {
		glfwSetWindowSize(window, width, height);
	}
	void setPosition(int x, int y) {
		glfwSetWindowPos(window, x, y);
	}

	void show() {
		glfwShowWindow(window);
	}
	void hide() {
		glfwHideWindow(window);
	}
	void close() {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	void fullscreen() {
		//glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(),
	}

	void setTickFunc(void(*callback)(void)) {
		tickCallback = callback;
	}

	void setKeyboardPressFunc(void(*callback)(int)) {
		pressCallback = callback;
	}

	void setKeyboardReleaseFunc(void(*callback)(int)) {
		releaseCallback = callback;
	}

	void startLoop() {
		//TODO: Get threading to work.
		//loopThread = new thread(loop, this);
		_loop();
	}

	void _loop() {
		glfwSetKeyCallback(window, keyHandler);

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glfwMakeContextCurrent(window);
			if (tickCallback != nullptr) {
				tickCallback();
			}

			glfwSwapBuffers(window);
		}
	}

	private:	
	GLFWwindow *window;
	void(*tickCallback)(void);
	thread *loopThread;
};

void loop(GraphicsWindowGL *window) {
	window->_loop();
}