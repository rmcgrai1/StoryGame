#pragma once

#include "../IGraphicsSettings.h"

class GraphicsSettingsGL : public IGraphicsSettings {
	public:
	void clear() {
		clearColor4d(0, 0, 0, 0);
	}
	void clearColor4b(byte r, byte g, byte b, byte a) {
		clearColor4d(r/255., g/255., b/255., a/255.);
	}
	void clearColor4d(double r, double g, double b, double a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	private:
};