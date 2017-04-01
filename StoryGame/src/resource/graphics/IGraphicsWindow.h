#pragma once

#include <string>
using namespace std;

class IGraphicsWindow {
	public:
	virtual void setTitle(string) = 0;
	virtual void setSize(int, int) = 0;
	virtual void setPosition(int, int) = 0;

	virtual void setTickFunc(void(*callback)(void)) = 0;
	virtual void startLoop() = 0;

	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void close() = 0;
	virtual void fullscreen() = 0;

	virtual void setKeyboardPressFunc(void(*callback)(int)) = 0;
	virtual void setKeyboardReleaseFunc(void(*callback)(int)) = 0;

	private:
};