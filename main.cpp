#include "main.h"
#include "InitWindow.h"
#include "Cube.h"
#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



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
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		void main() {
			gl_Position = projection * view * model * vec4(aPos, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		void main() {
			FragColor = vec4(0.5, 0.0, 0.0, 1.0);
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
			GLint modelLoc = glGetUniformLocation(shader.ID, "model");
			GLint viewLoc = glGetUniformLocation(shader.ID, "view");
			GLint projLoc = glGetUniformLocation(shader.ID, "projection");

			//transformation matrices
			glm::mat4 model = glm::mat4(1.0f);
			//rotate the cube over time
			model = glm::rotate(model, static_cast<float>(SDL_GetTicks()) / 1000.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

			//pass matrices to the shader
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


			cube.draw();

			SDL_GL_SwapWindow(window);
	}

	clog << "PROGRAM EXITED" << endl;

	endSDL(SDLFlag::ALL);
	return 0;

}