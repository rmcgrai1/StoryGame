#pragma once

#include <GLFW/glfw3.h>
#include "../IGraphics.h"
#include "GraphicsSettingsGL.h"
#include "GraphicsPrimitiveGL.h"
#include "Graphics2DGL.h"
#include "GraphicsWindowGL.h"

class GraphicsGL : public IGraphics {
	public:
	GraphicsGL() {
		graphicsSettings = new GraphicsSettingsGL();

		GraphicsPrimitiveGL* gp = new GraphicsPrimitiveGL();
		graphicsPrimitive = gp;

		graphics2D = new Graphics2DGL(gp);
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
