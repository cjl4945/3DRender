#pragma once
#include "main.h"

const int WIDTH = 800, HEIGHT = 600;

extern SDL_Window* window;
extern SDL_GLContext context;


#define WINDOW  1
#define CONTEXT 2
#define GLEW 3
#define ALL 4




void setVersion();

int createWindow();

int createGLContext();

int initGLEW();

void endSDL(int flag);

void enableDepthTest();

void processEvents(bool& running);

void renderFrame();