#include "sdl.h"

SDL_Window* init_sdl() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(255);
    }

    SDL_Window* window = SDL_CreateWindow("sadplay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

        //Quit SDL subsystems
        SDL_Quit();
        exit(255);
    }

    SDL_Renderer* renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    // Clear winow
    SDL_RenderClear(renderer);

    //Update the surface
    SDL_UpdateWindowSurface(window);

    return window;
}

void draw_bar(SDL_Renderer* renderer, int x, int w, int bar_perc)
{
    // Color variables
    Uint8 r, g, b;

    int y_min = BORDER;
    int y_max = SCREEN_HEIGHT - BORDER;
    int y_span = y_max - y_min;
    int y_level = y_span * bar_perc / 100;

    int dy;
    for (dy = y_level; dy > 0; dy--)
    {
        int y = y_max - dy;

        int level_perc = (y_span - dy) * 100 / y_span;

        calculate_color(level_perc, &r, &g, &b);

        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer, x, y, x + w, y);
    }

}

void calculate_color(int perc, Uint8* r, Uint8* g, Uint8* b) {
    int calc_r = (100 - perc) * 255 / 50;
    int calc_g = perc * 255 / 50;
    int calc_b = 0;

    if (calc_r > 255) calc_r = 255;
    if (calc_g > 255) calc_g = 255;
    if (calc_b > 255) calc_b = 255;
    *r = (Uint8) calc_r;
    *g = (Uint8) calc_g;
    *b = (Uint8) calc_b;
}

void draw_bars(SDL_Renderer* renderer, channel_bar* cbar)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    // Clear winow
    SDL_RenderClear(renderer);

    int h_span = H_SPAN;

    int step = h_span / cbar->num;

    int c;
    for (c = 0; c <= cbar->num; c++) {
        draw_bar(renderer, BORDER + (c * step) + step / 5, step * 3 / 5, cbar->channels[c]);
    }
}

void reduce_bars(channel_bar* cbar, int diff) {
    int c;
    for (c = 0; c < cbar->num; c++) {
        if (cbar->channels[c] > 0) {
            cbar->channels[c] -= diff;
        }
    }
}

channel_bar* create_channel_bar(int num_channels)
{
    channel_bar* cbar = malloc(sizeof(channel_bar));
    cbar->num = num_channels;
    cbar->channels = malloc(sizeof(int) * num_channels);
    return cbar;
}

void destroy_channel_bar(channel_bar* cbar)
{
    free(cbar->channels);
    free(cbar);
}

Uint32 draw_bars_callback( Uint32 interval, void* param ) {
    int counter;
    timed_args* args = (timed_args*) param;
    int diff = (interval + 50) / 100;
    reduce_bars(args->channel_bar, diff);
    draw_bars(args->renderer, args->channel_bar);
    SDL_RenderPresent(args->renderer);
    return 1;
}