#pragma once

#include "IGraphicsPrimitive.h"
#include "IGraphicsWindow.h"

class IGraphics {
	public:
	virtual void init() = 0;

	IGraphicsPrimitive* getGraphicsPrimitive() {
		return graphicsPrimitive;
	}

	virtual IGraphicsWindow* createGraphicsWindow() = 0;

	private:
	IGraphicsPrimitive* graphicsPrimitive;
};

class NullGraphics : public IGraphics {
	public:
	void init() {}
	IGraphicsWindow* createGraphicsWindow() {return nullptr;}
};