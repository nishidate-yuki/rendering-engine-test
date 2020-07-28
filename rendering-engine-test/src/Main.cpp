#include <iostream>
#include "Engine.h"

int main(int argc, char** argv)
{
	std::cout << "Started\n";

	Engine engine;
	if (engine.Initialize()) {
		engine.RunLoop();
	}

	return 0;
}
