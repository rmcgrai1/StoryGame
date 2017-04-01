#pragma once

#include <GLFW/glfw3.h>
#include "../IGraphicsWindow.h"

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
		glfwSetKeyCallback(window, keyHandler);

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			if (tickCallback != nullptr) {
				tickCallback();
			}

			glfwSwapBuffers(window);
		}
	}

	private:
	GLFWwindow *window;
	void(*tickCallback)(void);	
};