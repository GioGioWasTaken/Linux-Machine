#include <SDL2/SDL.h>

int main() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
    return 1;
  }

  // Create a window
  SDL_Window *window =
      SDL_CreateWindow("Sound Player",          // Window title
                       SDL_WINDOWPOS_UNDEFINED, // Initial x position
                       SDL_WINDOWPOS_UNDEFINED, // Initial y position
                       800,                     // Width
                       600,                     // Height
                       SDL_WINDOW_SHOWN         // Flags
      );

  if (window == NULL) {
    fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Main loop
  SDL_Event event;
  int running = 1;
  while (running) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }
  }

  // Cleanup
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
