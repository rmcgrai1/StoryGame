#pragma once

class IManager {
	public:
	virtual void tick() = 0;

	private:
};

class NullManager : public IManager {
	public:
	void tick() {}
};