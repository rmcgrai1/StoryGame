#pragma once

#include "../IGraphics2D.h"
#include "GraphicsPrimitiveGL.h"

class Graphics2DGL : public IGraphics2D {
	public:
	Graphics2DGL(GraphicsPrimitiveGL *gp) : IGraphics2D(gp) {}
};