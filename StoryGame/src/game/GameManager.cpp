#include "GameManager.h"
#include "resource\ResourceLocator.h"
#include "resource\log\impl\ConsoleLog.h"

GameManager::GameManager() {};

#include <iostream>
using namespace std;

int main() {
	GameManager *gm = new GameManager();

	ResourceLocator* rl = ResourceLocator::get();
	rl->setLog(new ConsoleLog());

	ILog* log = ResourceLocator::get()->getLog();
	string str;

	int i = 0;

	while (true) {
		str = to_string(i);

		log->println(str);

		i++;
	}

	return 0;
}