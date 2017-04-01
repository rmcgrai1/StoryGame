#pragma once

#include "generic/data/byte.h"

class IGraphicsSettings {
	public:
	virtual void clear() = 0;
	virtual void clearColor4b(byte r, byte g, byte b, byte a) = 0;
	virtual void clearColor4d(double r, double g, double b, double a) = 0;

	private:
};