#pragma once

#include "generic/data/byte.h"

enum PrimitiveType {
	PRIMITIVE_POINTS,
	PRIMITIVE_LINES, PRIMITIVE_LINE_LOOP,
	PRIMITIVE_TRIANGLES,
	PRIMITIVE_QUADS
};

class IGraphicsPrimitive {
	public:
	virtual void begin(PrimitiveType) = 0;

	virtual void color4b(byte, byte, byte, byte) = 0;
	virtual void color4d(double, double, double, double) = 0;
	virtual void vertex2d(double, double) = 0;
	virtual void vertex3d(double, double, double) = 0;

	virtual void end() = 0;

	private:
};