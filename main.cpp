#include "main.h"
#include "InitWindow.h"
#include "Cube.h"

using namespace std;





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

	Cube cube;

	bool running = true;
	while (running)
	{
			processEvents(running);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cube.draw();

			SDL_GL_SwapWindow(window);
	}

	clog << "PROGRAM EXITED" << endl;

	endSDL(SDLFlag::ALL);
	return 0;

}