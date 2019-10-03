//Using SDL and standard IO
#include <stdio.h>

#include <SDL2/SDL.h>

#include "init.h"

int main(int argc, char *args[])
{
    //The window we'll be rendering to
    SDL_Window *window = init_sdl();

    //Wait two seconds
    SDL_Delay(2000);

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}