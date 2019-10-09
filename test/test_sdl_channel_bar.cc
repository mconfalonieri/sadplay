/*
 * sadplay - AdLib music player with graphics.
 * 
 * test_sdl_channel_bar.cc - test file for the SDL channel bar file.
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

#include <map>
#include <string>

const int TEST_CHANNELS_NUM = 8;

/**
 * Class used for accessing the channel bar fields.
 */
class sdl_channel_bar_test_access {
    public:
        sdl_channel_bar_test_access(sdl_channel_bar* channel_bar) :
                channel_bar(channel_bar) {

        }

        std::vector<int>& access_vector() {
            return channel_bar->channels;
        }

        SDL_mutex* access_mutex() {
            return channel_bar->mutex;
        }
    private:
        sdl_channel_bar* channel_bar;
};

/**
 * Tests the channel bar constructor.
 */
bool test_sdl_channel_bar_constructor() {
    sdl_channel_bar* channel_bar = new sdl_channel_bar(TEST_CHANNELS_NUM);
    sdl_channel_bar_test_access* accessor = new sdl_channel_bar_test_access(channel_bar);
    bool test_ok = (accessor->access_vector().size() == TEST_CHANNELS_NUM)
        && (accessor->access_mutex() != NULL);
    delete accessor;
    delete channel_bar;
    return test_ok;
}

// Loads the tests in the appropriate array.
void load_test_map(std::map<std::string, bool(*)()>& tests) {
    tests["sdl_channel_bar|sdl_channel_bar.sdl_channel_bar"] = test_sdl_channel_bar_constructor;
}