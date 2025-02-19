#pragma once
#include "main.h"

const int WIDTH = 800, HEIGHT = 600;

extern SDL_Window* window;
extern SDL_GLContext context;


enum class SDLFlag
{
	WINDOW = 1,
	CONTEXT = 2,
	GLEW = 3,
	ALL = 4

};




void setVersion();

int createWindow();

int createGLContext();

int initGLEW();

void endSDL(SDLFlag flag);

void enableDepthTest();

void processEvents(bool& running);

void renderFrame();