#pragma once

#include "IGraphicsSettings.h"
#include "IGraphicsPrimitive.h"
#include "IGraphics2D.h"
#include "IGraphicsWindow.h"

class IGraphics {
	public:
	virtual void init() = 0;

	IGraphicsSettings* getGraphicsSettings() {
		return graphicsSettings;
	}
	IGraphicsPrimitive* getGraphicsPrimitive() {
		return graphicsPrimitive;
	}
	IGraphics2D* getGraphics2D() {
		return graphics2D;
	}

	virtual IGraphicsWindow* createGraphicsWindow() = 0;

	protected:
	IGraphicsSettings* graphicsSettings;
	IGraphicsPrimitive* graphicsPrimitive;
	IGraphics2D* graphics2D;

	private:
};

class NullGraphics : public IGraphics {
	public:
	void init() {}
	IGraphicsWindow* createGraphicsWindow() {return nullptr;}
};