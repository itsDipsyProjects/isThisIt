#include "include/SDL2/SDL.h"
#include <stdio.h>

/*
 INFO VIKTIGT: fatta varför man måste ha .dll filen för att det ska fungera. 
 man måste också ha -lmingw32 för att det ska fungera det måste jag också fatta samt -l och vad det gör
 inte -L och -I för det fattar jag men -l är fortfarande lite konstigt
*/

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1; // Return an error code
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          800, 600, 
                                          SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1; // Return an error code
    }

    // Event loop
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0; // Exit the loop if the window is closed
            }
        }

        // Optionally, you can add rendering code here
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit(); // Quit SDL
    return 0; // Successful exit
}
