/*
 * sadplay - AdLib music player with graphics.
 * 
 * sdl_driver.cc - implementation for SDL channel bar.
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
        
#include "sdl_channel_bar.h"

// The callback for the SDL timer.
extern "C" int sdl_channel_bar_callback(Uint32 time_elapsed, void* param) {
    sdl_channel_bar* channel_bar = (sdl_channel_bar*) param;
    channel_bar->time_elapsed(time_elapsed);
    return 1;
}

// Constructor: it creates the channel vector and initializes the mutex.
sdl_channel_bar::sdl_channel_bar(int num_channels): mutex(NULL), channels(8) {
    this->mutex = SDL_CreateMutex();
    reset_channels();
}

// Destructor: destroys the mutex.
sdl_channel_bar::~sdl_channel_bar() {
    SDL_DestroyMutex(this->mutex);
}

// Updates the specified channel.
void sdl_channel_bar::update(int channel, int value) {
    int status = SDL_LockMutex(this->mutex);
    if (status != 0) {
        return;
    }
    this->channels[channel] = value;
    SDL_UnlockMutex(this->mutex);
}

// Updates all channels.
void sdl_channel_bar::update_all(const int values[]) {
    int status = SDL_LockMutex(this->mutex);
    for (int c = 0; c < this->channels.size(); c++) {
        int new_value = (values[c] > 100)? 100 : values[c];
        this->channels[c] = new_value;
    }
    SDL_UnlockMutex(this->mutex);
}

// Reset all channels
void sdl_channel_bar::reset_channels() {
    int zeroes[this->channels.size()] = {};
    this->update_all(zeroes);
}

// Executes the operations associated with the timer.
void sdl_channel_bar::time_elapsed(Uint32 time_elapsed) {
    int status = SDL_LockMutex(this->mutex);
    if (status != 0) {
        return;
    }
    for (int c = 0; c < this->channels.size(); c++) {
        int& ch = this->channels[c];
        if (ch > 0) {
            int new_value = ch - (time_elapsed * 100 / DECAY_TIMER);
            ch = (new_value < 0)? 0 : new_value;
        }
    }
    SDL_UnlockMutex(this->mutex);
}
