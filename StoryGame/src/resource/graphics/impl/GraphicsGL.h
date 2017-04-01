#pragma once

#include <GLFW/glfw3.h>
#include "../IGraphics.h"
#include "GraphicsWindowGL.h"

class GraphicsGL : public IGraphics {
	public:
	GraphicsGL() {
	}

	void init() {
		ResourceLocator::get()->getLog()->println("Initialized!");

		glfwInit();
	};

	IGraphicsWindow* createGraphicsWindow() {
		return new GraphicsWindowGL();
	}

	private:
};
