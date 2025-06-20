#include "engine.h"

int main() {
	Engine engine;
	if (!engine.init(800, 600)) {
		return 1;
	}
	engine.run();
	engine.shutdown();
	return 0;
}
