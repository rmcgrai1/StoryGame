#pragma once

#include <GLFW/glfw3.h>
#include "../IGraphicsPrimitive.h"

class GraphicsPrimitiveGL : public IGraphicsPrimitive {
	public:
	void begin(PrimitiveType type) {
		int glType = -1;

		switch (type) {
			case PRIMITIVE_POINTS:	glType = GL_POINTS;		break;
			case PRIMITIVE_LINES:		glType = GL_LINES;		break;
			case PRIMITIVE_TRIANGLES: glType = GL_TRIANGLES;	break;
			case PRIMITIVE_QUADS:		glType = GL_QUADS;		break;
		}

		if (glType != -1) {
			glBegin(glType);
		}
	}

	void color4b(byte r, byte g, byte b, byte a) {
		glColor4b(r, g, b, a);
	}

	void color4d(double r, double g, double b, double a) {
		glColor4d(r, g, b, a);
	}

	void vertex2d(double x, double y) {
		glVertex2d(x, y);
	}

	void vertex3d(double x, double y, double z) {
		glVertex3d(x, y, z);
	}

	void end() {
		glEnd();
	}

	private:
};