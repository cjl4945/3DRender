#include "InitWindow.h"


using namespace std;

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
        endSDL(SDLFlag::WINDOW);
        return -1;
    }
    return 1;
}

int createGLContext() 
{
    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        cerr << "Failed to create OpenGL context: " << SDL_GetError() << endl;
        endSDL(SDLFlag::CONTEXT);
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
        endSDL(SDLFlag::GLEW);
        return -1;
    }
    return 1;
}

void enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void processEvents(bool& running, Camera& camera, float deltaTime, bool &paused)
{
    //Handle keyboard input
    SDL_PumpEvents();
    if (!paused)
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W])
            camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
        if (state[SDL_SCANCODE_S])
            camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
        if (state[SDL_SCANCODE_A])
            camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
        if (state[SDL_SCANCODE_D])
            camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) 
        {
            running = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                paused = !paused;

                SDL_ShowCursor(paused ? SDL_ENABLE : SDL_DISABLE);
            }
        }
       


        if (!paused && !ImGui::GetIO().WantCaptureMouse && event.type == SDL_MOUSEMOTION)
        {
            camera.processMouseMovement(static_cast<float>(event.motion.xrel),
                -static_cast<float>(event.motion.yrel));
        }
    }

}

void renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void endSDL(SDLFlag flag)
{
    switch (flag) 
    {
    case SDLFlag::WINDOW:
        SDL_Quit();
        break;
    case SDLFlag::CONTEXT:
        SDL_DestroyWindow(window);
        SDL_Quit();
        break;

    case SDLFlag::GLEW:
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        break;
    case SDLFlag::ALL:
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        break;
    default:
        cerr << "Not a valid Flag" << endl;
        break;
    }
}
