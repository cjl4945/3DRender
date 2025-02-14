#include "main.h"
#include "InitWindow.h"
#include "geometry.h"







int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "Failed to initialize SDL: " << SDL_GetError() << endl;
		return -1;
	}

	setVersion();
	if (!createWindow()) return -1;
	if (!createGLContext()) return -1;

	initGLEW();
	enableDepthTest();

	bool running = true;
	while (running)
	{
		processEvents(running);
		renderFrame();
	}

	endSDL(ALL);
	return 0;

}