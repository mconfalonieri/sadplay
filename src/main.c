//Using SDL and standard IO
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "sdl.h"

int main(int argc, char *args[])
{
    channel_bar* cbar = create_channel_bar(8);
    int c;
    srand(time(NULL));
    for (c = 0; c < cbar->num; c++) {
        cbar->channels[c] = rand() % 101;
    }
    //The window we'll be rendering to
    SDL_Window *window = init_sdl();

    int counter;
    for (counter = 0; counter < 100; counter++)
    {
        draw_bars(window, cbar);
        SDL_Renderer* renderer = SDL_GetRenderer(window);
        SDL_RenderPresent(renderer);
        
        reduce_bars(cbar);
        SDL_Delay(10);
    }


    //Wait ten seconds
    SDL_Delay(10000);

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    destroy_channel_bar(cbar);

    return 0;
}