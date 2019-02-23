#if defined(_WIN32)
#include <windows.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

SDL_Window *mainWindow;
SDL_GLContext mainContext;

void CheckSDLError(std::string errmsg, int line = -1)
{
  std::string error = SDL_GetError();

  std::cout << errmsg << std::endl;

  if (error != "")
  {
    std::cout << "SDL Error : " << error << std::endl;

    if (line != -1)
      std::cout << "\nLine : " << line << std::endl;

    SDL_ClearError();
  }
}

bool SetOpenGLAttributes()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  glAlphaFunc(GL_GREATER, 0.0);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//  glEnable(GL_CULL_FACE);
//  glDisable(GL_CULL_FACE);

//  glCullFace(GL_FRONT);
  return true;
}

#if defined(_WIN32)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char **argv)
#endif
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    CheckSDLError("Failed to init SDL", __LINE__);
    return 0;
  }

  mainWindow = SDL_CreateWindow("TEST_GLLLLL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL /*| SDL_WINDOW_FULLSCREEN*/);

  if (!mainWindow)
  {
    CheckSDLError("Unable to create window", __LINE__);
    return false;
  }

  mainContext = SDL_GL_CreateContext(mainWindow);

  SetOpenGLAttributes();

  SDL_GL_SetSwapInterval(0);

  glewInit();

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glClearDepth(1.f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.f, 1.f, 1.f, 2000.f);
  glEnable(GL_TEXTURE_2D);

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP);

  SDL_ShowCursor(1);

  while (1)
  {
    SDL_PumpEvents();

    SDL_GL_SwapWindow(mainWindow);
  }

  return 0;
}

