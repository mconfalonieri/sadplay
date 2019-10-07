//Using SDL and standard IO
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "sdl.h"

int main(int argc, char *args[])
{
    channel_bar *cbar = create_channel_bar(8);
    int c;
    srand(time(NULL));
    for (c = 0; c < cbar->num; c++)
    {
        cbar->channels[c] = rand() % 101;
    }
    //The window we'll be rendering to
    SDL_Window* window = init_sdl();

    SDL_Renderer* renderer = SDL_GetRenderer(window);
    timed_args* timed_args = malloc(sizeof(timed_args));
    timed_args->channel_bar = cbar;
    timed_args->renderer = renderer;

    draw_bars_callback(0, timed_args);

    SDL_TimerID timerID = SDL_AddTimer(3000, draw_bars_callback, "100 milliseconds waited!");
    int quit = 0;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = -1;
            }
        }
    }

    //Remove timer in case the call back was not called
    SDL_RemoveTimer(timerID);

    free(timed_args);

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    destroy_channel_bar(cbar);

    return 0;
}
