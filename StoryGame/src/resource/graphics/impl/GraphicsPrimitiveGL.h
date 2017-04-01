#include <GLFW/glfw3.h>
#include "../IGraphicsPrimitive.h"

class GraphicsPrimitive : public IGraphicsPrimitive {
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

	void color4d(double r, double g, double b, double a) {
		glColor4d(r, g, b, a);
	}

	void vertex3d(double x, double y, double z) {
		glVertex3d(x, y, z);
	}

	void end() {
		glEnd();
	}

	private:
};