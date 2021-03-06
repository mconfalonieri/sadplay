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

#include <iostream>

#include "spectrum_analyzer.h"

// Constructor.
sdl_display_driver::sdl_display_driver(): mutex(NULL), timer_player(0),
        cbar(NULL), freq_bar(NULL), analyzer(NULL), audio_dev_id(0) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(255);
    }
    colors_table = new rgb[101];
    prepare_colors_table();

    mutex = SDL_CreateMutex();

}

// Destructor.
sdl_display_driver::~sdl_display_driver() {
    stop();
    
    int status = SDL_LockMutex(mutex);
    if (status != 0) {
        printf("Cannot lock mutex");
        exit(127);
    }

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    
    SDL_UnlockMutex(mutex);
    SDL_DestroyMutex(mutex);
    mutex = NULL;

    delete analyzer;
    delete freq_bar;
    delete channels;
    delete cbar;

 
    delete[] colors_table;

    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

// Initializer
bool sdl_display_driver::initialize(int num_channels) {  
    window = SDL_CreateWindow("sadplay",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n",
                SDL_GetError());

        return false;
    }

    renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n",
                SDL_GetError());

        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    // Clear the window
    SDL_RenderClear(renderer);

    // Update the surface
    SDL_RenderPresent(renderer);

    // Draws a red square
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_Rect rect; rect.x = 10; rect.y = 10; rect.h = 10; rect.w = 10;
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    // Set last render ticks
    last_update_ticks = SDL_GetTicks();

    // Create the channel bar.
    cbar = new sdl_channel_bar(num_channels);
    channels = new int[num_channels];

    freq_bar = new frequency_bar(cbar);

    analyzer = new spectrum_analyzer(freq_bar);

    return true;
}

// Prepares the colors table.
void sdl_display_driver::prepare_colors_table() {
    for (int i = 0; i <= 100; i++) {
        calculate_color(colors_table[i], i);
    }
}

// Normalizes colors.
inline void sdl_display_driver::normalize_color(rgb &color,
        int r, int g, int b) {
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
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, x, y, x + width, y);
    }

}

// Draws all the bars
void sdl_display_driver::draw_bars() {
    int num_channels = cbar->get_numchannels();
    int step = H_SPAN / num_channels;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    cbar->get_channels(channels);
    for (int c = 0; c < num_channels; c++) {
        draw_bar(BORDER + (c * step) + step / 5, step * 3 / 5, channels[c]);
    }
    SDL_RenderPresent(renderer);
}

void sdl_display_driver::prepare_rectangle(SDL_Rect &rect, int x, int y,
        int w, int h) {
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
    if (renderer == NULL) return;
    draw_bars();
    SDL_UnlockMutex(mutex);
}

// Returns the channel bar instance.
channel_bar* sdl_display_driver::get_channel_bar() {
    return this->cbar;
}

// Updates the channel bar.
void sdl_display_driver::update_channel_bar(Uint32 time_elapsed) {
    update_channel_bar();
    cbar->time_elapsed(time_elapsed);
}

const sdl_display_driver::rgb sdl_display_driver::BLACK = { 0, 0, 0 };

bool sdl_display_driver::play(adplug_player* player) {
    stop();
    this->player = player;
    setup_audio_spec(spec);

    audio_dev_id = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    if (audio_dev_id < 0) return false;

    SDL_PauseAudioDevice(audio_dev_id, 0);
    return true;
}

void sdl_display_driver::pause() {
    SDL_PauseAudioDevice(audio_dev_id, 1);
}

void sdl_display_driver::cont() {
    SDL_PauseAudioDevice(audio_dev_id, 0);
}

void sdl_display_driver::stop() {
    if (this->player != NULL) {
        close_audio_device();
        this->player = NULL;
    }
}

void sdl_display_driver::audio_callback(void* param, Uint8* audiobuf,
        int len) {
    sdl_display_driver* self = (sdl_display_driver*) param;
    unsigned char sample_size = self->spec.channels *
            (self->spec.format == AUDIO_U8 ? 1 : 2);

    self->player->fill_buffer((void*) audiobuf, len, sample_size);
    
    // Number of stereo 16-bit samples.
    int n = len / 4;
    self->analyzer->perform(n, (const short*) audiobuf);
}

void sdl_display_driver::close_audio_device() {
    if (audio_dev_id > 0) {
        SDL_CloseAudioDevice(audio_dev_id);
        audio_dev_id = 0;
    }
}

void sdl_display_driver::render() {
    Uint32 ticks = SDL_GetTicks();
    Uint32 elapsed_ticks = ticks - last_update_ticks;
    if (elapsed_ticks >= TIMER_INTERVAL) {
        update_channel_bar(elapsed_ticks);
        last_update_ticks = ticks;
    }

    
}