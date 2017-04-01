#pragma once

#include "IGraphicsPrimitive.h"

class IGraphics2D {
	public:
	IGraphics2D(IGraphicsPrimitive *gp) {
		this->gp = gp;
	}

	virtual void drawPoint(double x, double y) {
		gp->begin(PRIMITIVE_POINTS);
		gp->vertex2d(x, y);
		gp->end();
	}

	virtual void drawLine(double x1, double y1, double x2, double y2) {
		gp->begin(PRIMITIVE_LINES);
		gp->vertex2d(x1, y1);
		gp->vertex2d(x2, y2);
		gp->end();
	}

	virtual void drawRectangle(double x, double y, double w, double h, bool isFilled) {
		gp->begin(isFilled ? PRIMITIVE_QUADS : PRIMITIVE_LINE_LOOP);
		gp->vertex2d(x, y);
		gp->vertex2d(x + w, y);
		gp->vertex2d(x + w, y + h);
		gp->vertex2d(x, y + h);
		gp->end();
	}
	virtual void strokeRectangle(double x, double y, double w, double h) {
		drawRectangle(x, y, w, h, false);
	}
	virtual void fillRectangle(double x, double y, double w, double h) {
		drawRectangle(x, y, w, h, true);
	}

	private:
	IGraphicsPrimitive* gp;
};