#include "main.h"
#include "InitWindow.h"
#include "Cube.h"
#include "Shader.h"

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


	const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec3  aPos;
		void main() {
			gl_Position = vec4(aPos, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		void main() {
			FragColor = vec4(1.0, 0.5, 0.2, 1.0);
		}
	)";

	Shader shader(vertexShaderSource, fragmentShaderSource);



	Cube cube;

	bool running = true;
	while (running)
	{
			processEvents(running);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shader.use();
			cube.draw();

			SDL_GL_SwapWindow(window);
	}

	clog << "PROGRAM EXITED" << endl;

	endSDL(SDLFlag::ALL);
	return 0;

}