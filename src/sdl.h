#ifndef _SADPLAY_SDL_H_
#define _SADPLAY_SDL_H_

#include <SDL.h>

//Screen dimension constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define BORDER 40
#define H_SPAN (SCREEN_WIDTH - (2 * BORDER))

typedef struct _struct_channel_bar_ {
    int num;
    int* channels;
} channel_bar;

typedef struct _struct_timed_args_ {
    channel_bar* channel_bar;
    SDL_Renderer* renderer;
} timed_args;

/**
 * \brief Initializes the SDL system.
 * 
 * \return the window structure or NULL
 */
SDL_Window* init_sdl();

/**
 * \brief Draws a bar on the window.
 * 
 * This function draws a full rainbow bar in the window.
 * 
 * \param window pointer to the window where the bar should be drawn
 */
void draw_bar(SDL_Renderer* renderer, int x, int w, int bar_perc);

void calculate_color(int perc, Uint8* r, Uint8* g, Uint8* b);

void draw_bars(SDL_Renderer* renderer, channel_bar* cbar);

void reduce_bars(channel_bar* cbar, int diff);

channel_bar* create_channel_bar(int num_channels);

void destroy_channel_bar(channel_bar* cbar);

Uint32 draw_bars_callback( Uint32 interval, void* param );

#endif // _SADPLAY_SDL_H_