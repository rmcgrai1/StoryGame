#pragma once

#include "graphics/IGraphics.h"
#include "log/ILog.h"

class ResourceLocator {
	public:
	static ResourceLocator* get();

	void setGraphics(IGraphics*);
	IGraphics* getGraphics();

	void setLog(ILog*);
	ILog* getLog();


	private:
	static ResourceLocator* instance;

	ResourceLocator();
	IGraphics
		*NULL_GRAPHICS = new NullGraphics(),
		*graphics = NULL_GRAPHICS;
	ILog
		*NULL_LOG = new NullLog(),
		*log = NULL_LOG;
};