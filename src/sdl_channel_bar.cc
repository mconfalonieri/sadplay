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

// Number of channels.
const int sdl_channel_bar::NUM_CHANNELS = 12;

// Frequency limits on each channel.
const double sdl_channel_bar::CHANNEL_LIMITS[] = {
        60.0,       170.0,      310.0,      600.0,
        1000.0,     3000.0,     6000.0,     14000.0,
        16000.0,    18000.0,    20000.0,    100000.0
};

// Constructor: it creates the channel vector and initializes the mutex.
sdl_channel_bar::sdl_channel_bar(): mutex(NULL),
        channels(NUM_CHANNELS) {
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
    int& ch = this->channels[channel];
    int new_value = (value > 100)? 100 : 
                ((value < 0)? 0 : value);
    if (new_value > ch) {
        ch = new_value;
    }
    SDL_UnlockMutex(this->mutex);
}

// Updates all channels.
void sdl_channel_bar::update_all(const int values[]) {
    int status = SDL_LockMutex(this->mutex);
    if (status != 0) {
        return;
    }
    for (int c = 0; c < this->channels.size(); c++) {
        int& ch = this->channels[c];
        int new_value = (values[c] > 100)? 100 : 
                ((values[c] < 0)? 0 : values[c]);
        if (new_value > ch) {
            ch = new_value;
        }
    }
    SDL_UnlockMutex(this->mutex);
}

// Reset all channels
void sdl_channel_bar::reset_channels() {
   int status = SDL_LockMutex(this->mutex);
    if (status != 0) {
        return;
    }
    for (int c = 0; c < this->channels.size(); c++) {
        this->channels[c] = 0;
    }
    SDL_UnlockMutex(this->mutex);
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

const int sdl_channel_bar::get_numchannels() {
    int status = SDL_LockMutex(this->mutex);
    if (status != 0) {
        return 0;
    }
    int num_channels = this->channels.size();
    SDL_UnlockMutex(this->mutex);
    return num_channels;
}

const double* sdl_channel_bar::get_channel_limits() {
    return CHANNEL_LIMITS;
}

void sdl_channel_bar::get_channels(int* channels) {
    int status = SDL_LockMutex(this->mutex);
    if (status != 0) {
        return;
    }
    for (int i = 0; i < this->channels.size(); i++) {
        int value = this->channels[i];
        channels[i] = value;
    }
    SDL_UnlockMutex(this->mutex);
}