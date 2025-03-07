#include "main.h"
#include "InitWindow.h"
#include "Cube.h"
#include "Shader.h"
#include "Room.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>




using namespace std;





int main(int argc, char** argv) {
	Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	static float lightPos[3] = { 1.2f, 2.0f, 2.0f };
	static float objectColor[3] = { 1.0f, 0.5f, 0.31f };

	
	cout << "Size of float :" << sizeof(float) << endl;
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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init("#version 330");

	//start loading texture and create an object
	ResourceManager resourceManager;
	resourceManager.loadResourceAsync("resources/textures/milkyWay.jpg");

	GLuint platformTexture = 0;
	ResourceData resData;
	if (resourceManager.getNextResource(resData))
	{
		if (resData.data)
		{
			glGenTextures(1, &platformTexture);
			glBindTexture(GL_TEXTURE_2D, platformTexture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			GLenum format = (resData.channels == 4) ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, resData.width, resData.height, 0, format, GL_UNSIGNED_BYTE, resData.data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(resData.data);
			cout << "Loaded texture: " << resData.name << endl;

		}
	}


	const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec3  aPos;
		layout(location = 1) in vec3 aNormal;
		layout(location = 2) in vec2 aTexCoords;


		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		
		out vec3 FragPos;
		out vec3 Normal;
		out vec2 TexCoords;


		void main() {
			// Calculate the vertex position in world space.
			FragPos = vec3(model * vec4(aPos, 1.0));
			// Transform the normal using the inverse transpose of the model matrix.
			Normal = mat3(transpose(inverse(model))) * aNormal;
			TexCoords = aTexCoords;
			gl_Position = projection * view * vec4(FragPos, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		in vec3 FragPos;
		in vec3 Normal;
		in vec2 TexCoords;

		out vec4 FragColor;

		uniform vec3 lightPos;
		uniform vec3 viewPos;
		uniform vec3 lightColor;
		uniform vec3 objectColor;
		uniform sampler2D texture1;

		void main() {
			//Ambient lighting
			float ambientStrength = 0.3;
			vec3 ambient = ambientStrength * lightColor;

			//Diffuse lighting
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(lightPos - FragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = diff * lightColor;

			//Specular lighting
			float specularStrength = 0.5;
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
			vec3 specular = specularStrength * spec * lightColor;
	
			vec3 lighting = (ambient + diffuse + specular);

			//sample the texture
			vec4 textColor = texture(texture1, TexCoords);

			FragColor = vec4(lighting * objectColor, 1.0) * textColor;
		}
	)";

	Shader shader(vertexShaderSource, fragmentShaderSource);
	Cube cube;
	Room room;

	bool running = true;
	bool paused = false;
	while (running)
	{
			float currentFrame = SDL_GetTicks() / 1000.f;
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			processEvents(running, camera, deltaTime, paused);

			//Start ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			//---Building gui
			
			ImGui::SetNextWindowSize(ImVec2(400, 131), ImGuiCond_Appearing);
			ImGui::Begin("Debug Controls");
			
			ImGui::Text("Parameter-Tweak, Press ESC key to unlock/lock movement");
			ImGui::Text("Width: %0.1f	Height:%0.1f", ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
			

			//light position parameter tweak
			
			ImGui::SliderFloat3("Light Position", lightPos, -10.0f, 10.0f);
			
				

			//object color tweak 
	
			ImGui::ColorEdit3( "Object Color", objectColor);
			if (ImGui::Button("Resume"))
			{
				paused = false;
				SDL_ShowCursor(SDL_DISABLE);
			}
			ImGui::SameLine();
			if (ImGui::Button("Pause"))
			{
				paused = true;
				SDL_ShowCursor(SDL_ENABLE);
			}

				

			ImGui::End();

				//code the gui right here
			
			

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shader.use();
			GLint modelLoc = glGetUniformLocation(shader.ID, "model");
			GLint viewLoc = glGetUniformLocation(shader.ID, "view");
			GLint projLoc = glGetUniformLocation(shader.ID, "projection");
			GLint lightPosLoc = glGetUniformLocation(shader.ID, "lightPos");
			GLint viewPosLoc = glGetUniformLocation(shader.ID, "viewPos");
			GLint lightColorLoc = glGetUniformLocation(shader.ID, "lightColor");
			GLint objectColorLoc = glGetUniformLocation(shader.ID, "objectColor");
			GLint texture1 = glGetUniformLocation(shader.ID, "texture1");

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			//transformation matrices
			int width, height;
			SDL_GetWindowSize(window, &width, &height);
			glm::mat4 view = camera.getViewMatrix();
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

			//Change the background color
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			//pass matrices to the shader
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			//Set lighting uniforms
			glUniform3f(lightPosLoc, lightPos[0], lightPos[1], lightPos[2]);
			
			glUniform3f(viewPosLoc, 0.0f, 0.0f, 5.0f);
			glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

			//Bind the texture for the platform
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, platformTexture);
			glUniform1i(texture1, 0);



			
			

			// ---Draw the platform
			glm::mat4 platformModel = glm::mat4(1.0f);
			platformModel = glm::translate(platformModel, glm::vec3(0.0f, 0.0f, 0.0f));
			platformModel = glm::scale(platformModel, glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(platformModel));

			glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);
			room.draw();

			//--- Draw the cube
			//Translate the cube so it sits on top of the platform, moving up 0.5 (x , y** , z )
			glm::mat4 cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.5f, 0.0f));

			cubeModel = glm::rotate(cubeModel, static_cast<float>(SDL_GetTicks()) / 1000.0f, glm::vec3(0.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
			glUniform3f(objectColorLoc, objectColor[0], objectColor[1], objectColor[2]);


			cube.draw();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			SDL_GL_SwapWindow(window);
	}

	clog << "PROGRAM EXITED" << endl;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	endSDL(SDLFlag::ALL);
	return 0;

}