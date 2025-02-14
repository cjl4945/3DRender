#include "InitWindow.h"
#include "geometry.h"

SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;

void setVersion() 
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

int createWindow()
{
    window = SDL_CreateWindow("Cube Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        endSDL(WINDOW);
        return -1;
    }
    return 1;
}

int createGLContext() 
{
    if (!window) return - 1;
    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        cerr << "Failed to create OpenGL context: " << SDL_GetError() << endl;
        endSDL(CONTEXT);
        return -1;
    }
    return 1;
}

int initGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        cerr << "Failed to initialize GLEW" << endl;
        endSDL(GLEW);
        return -1;
    }
    return 1;
}

void enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void processEvents(bool& running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) 
        {
            running = false;
        }
    }
}

void renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    glBindVertexArray(VAO)
}

void endSDL(int flag)
{
    switch (flag) 
    {
    case WINDOW:
        SDL_Quit();
        break;
    case CONTEXT:
        SDL_DestroyWindow(window);
        SDL_Quit();
        break;

    case GLEW:
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        break;
    case ALL:
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        break;
    default:
        cerr << "Not a valid Flag" << endl;
        break;
    }
}
