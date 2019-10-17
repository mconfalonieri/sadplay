/*
 * sadplay - AdLib music player with graphics.
 * 
 * sdl_driver.cc - Implementation for SDL display driver.
 * 
 * Copyright (C) 2019 Marco Confalonieri <marco at marcoconfalonieri.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "sdl_driver.h"

#include "spectrum_analyzer.h"

// Implementation of the callback.
extern "C" Uint32 sdl_channel_bar_callback(Uint32 time_elapsed, void* param) {
    sdl_display_driver* driver = (sdl_display_driver*) param;
    driver->update_channel_bar(time_elapsed);
    return sdl_display_driver::TIMER_INTERVAL;
}

// Constructor.
sdl_display_driver::sdl_display_driver(): mutex(NULL), timer_id(0),
        timer_player(0), cbar(NULL), freq_bar(NULL), analyzer(NULL) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(255);
    }
    colors_table = new rgb[101];
    prepare_colors_table();

    mutex = SDL_CreateMutex();

}

// Destructor.
sdl_display_driver::~sdl_display_driver() {
    if (analyzer != NULL) delete analyzer;
    if (freq_bar != NULL) delete freq_bar;
    if (cbar != NULL) delete cbar;

    if (timer_id != 0) {
        SDL_RemoveTimer(timer_id);
    }

    if (mutex != NULL) {
        SDL_UnlockMutex(mutex);
    }

    delete[] colors_table;

    //Quit SDL subsystems
    SDL_Quit();
}

// Initializer
bool sdl_display_driver::initialize(int num_channels) {  
    window = SDL_CreateWindow("sadplay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

        return false;
    }

    renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    // Clear winow
    SDL_RenderClear(renderer);

    //Update the surface
    SDL_RenderPresent(renderer);


    // Create the channel bar.
    cbar = new sdl_channel_bar(num_channels);

    freq_bar = new frequency_bar(cbar);

    analyzer = new spectrum_analyzer(freq_bar);

    timer_id = SDL_AddTimer(TIMER_INTERVAL, sdl_channel_bar_callback, this);

    return true;
}

// Prepares the colors table.
void sdl_display_driver::prepare_colors_table() {
    for (int i = 0; i <= 100; i++) {
        calculate_color(colors_table[i], i);
    }
}

// Normalizes colors.
inline void sdl_display_driver::normalize_color(rgb &color, int r, int g, int b) {
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    color.r = (Uint8) r;
    color.g = (Uint8) g;
    color.b = (Uint8) b;
}

// Draws a bar.
void sdl_display_driver::draw_bar(int x, int width, int level) {
    int y_min = BORDER;
    int y_max = SCREEN_HEIGHT - BORDER;
    int y_span = y_max - y_min;
    int y_level = y_span * level / 100;

    for (int dy = y_level; dy > 0; dy--) {
        // LED effect
        if (!(dy % 4)) continue;

        int y = y_max - dy;
        int actual_level = (y_span - dy) * 100 / y_span;

        const rgb &color = colors_table[actual_level];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, x, y, x + width, y);
    }

}

// Draws all the bars
void sdl_display_driver::draw_bars() {
    int num_channels = cbar->get_numchannels();
    int step = H_SPAN / num_channels;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    int* channels = new int[num_channels];
    cbar->get_channels(channels);
    for (int c = 0; c < num_channels; c++) {
        draw_bar(BORDER + (c * step) + step / 5, step * 3 / 5, channels[c]);
    }
    SDL_RenderPresent(renderer);
    delete[] channels;
}

void sdl_display_driver::prepare_rectangle(SDL_Rect &rect, int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void sdl_display_driver::setup_audio_spec(SDL_AudioSpec &spec) {
    spec.freq = spectrum_analyzer::SAMPLING_RATE;
    spec.format = AUDIO_S16SYS;
    spec.channels = 2;
    spec.samples = spectrum_analyzer::IN_BUFFER_SIZE;
    spec.callback = audio_callback;
    spec.userdata = this;
}
// Calculates the color.
void sdl_display_driver::calculate_color(rgb &color, int level) {
    int r = (100 - level) * 255 / 50;
    int g = level * 255 / 50;
    int b = 0;

    normalize_color(color, r, g, b);
}

// Updates the channel bar when new values are available.
void sdl_display_driver::update_channel_bar() {
    int status = SDL_LockMutex(mutex);
    if (status != 0) {
        printf("Cannot lock mutex");
        return;
    }
    draw_bars();
    SDL_UnlockMutex(mutex);
}

// Returns the channel bar instance.
channel_bar* sdl_display_driver::get_channel_bar() {
    return this->cbar;
}

// Updates the channel bar. It is called by the callback.
void sdl_display_driver::update_channel_bar(Uint32 time_elapsed) {
    update_channel_bar();
    cbar->time_elapsed(time_elapsed);
}

const sdl_display_driver::rgb sdl_display_driver::BLACK = { 0, 0, 0 };

bool sdl_display_driver::play(adplug_player* player) {
    this->player = player;
    setup_audio_spec(spec);
    if (SDL_OpenAudio(&spec, NULL) < 0) {
        return false;
    }
    printf("Setup completed.\n");
    SDL_PauseAudio(0);
    return true;
}

void sdl_display_driver::audio_callback(void* param, Uint8* audiobuf, int len) {
    sdl_display_driver* self = (sdl_display_driver*) param;
    unsigned char sample_size = self->spec.channels * (self->spec.format == AUDIO_U8 ? 1 : 2);
    self->player->fill_buffer((void*) audiobuf, len, sample_size);
    self->analyzer->perform(len / 4, (const short*) audiobuf);
    if (self->player->is_ended()) {
        SDL_CloseAudio();
    }
}