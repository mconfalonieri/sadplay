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

#include <iostream>
#include <map>
#include <string>

const int TEST_CHANNELS_NUM = 8;
const int TEST_CHANNEL_VALUES[] = {10, 11, 12, 13, 14, 15, 16, 17};
const int TEST_CHANNEL_VALUES2[] = {20, 21, 22, 23, 24, 25, 26, 27};
const int TEST_CHANNEL_ZEROES[] = {0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Class used for accessing the channel bar fields.
 */
class sdl_channel_bar_test_access {
    public:
        /**
         * Constructor. It creates an accessor for the selected channel bar.
         * 
         * @param   channel_bar     channel bar to be accessed.
         */ 
        sdl_channel_bar_test_access(sdl_channel_bar* channel_bar) :
                channel_bar(channel_bar) {

        }

        /**
         * Provides access to the channel vector.
         * 
         * @return  the channel vector as reference
         */
        std::vector<int>& access_vector() {
            return channel_bar->channels;
        }

        /**
         * Returns the mutex.
         * 
         * @return  the mutex
         */
        SDL_mutex* get_mutex() {
            return channel_bar->mutex;
        }

        /**
         * Sets the mutex.
         * 
         * @param   new_mutex       the new mutex pointer
         */   
        void set_mutex(SDL_mutex* new_mutex) {
            channel_bar->mutex = new_mutex;
        }

        /**
         * Returns the channel bar.
         * 
         * @return  the channel bar
         */
        sdl_channel_bar* get_channel_bar() {
            return this->channel_bar;
        }

    private:
        /**
         * The channel bar.
         */
        sdl_channel_bar* channel_bar;
};

/**
 * Checks the values present in the channels towards a given array.
 * 
 * @param   accessor        pointer to the accessor
 * @param   values          array of values
 * 
 * @return  true if the values are as expected
 */
bool check_channels(sdl_channel_bar_test_access* accessor, const int values[]) {
    bool test_ok;
    for (int i = 0; i < TEST_CHANNELS_NUM; i++) {
        test_ok = (accessor->access_vector()[i] == values[i]);
        if (!test_ok) {
            break;
        }
    }
    return test_ok;
}

/**
 * Creates a new channel bar and accessor instance.
 * 
 * @param   channel_bar     reference to the channel bar pointer
 * @param   accessor        reference to the accessor pointer
 */
void create_test_harness(sdl_channel_bar* &channel_bar, sdl_channel_bar_test_access* &accessor) {
    SDL_Init(0);
    channel_bar = new sdl_channel_bar(TEST_CHANNELS_NUM);
    accessor = new sdl_channel_bar_test_access(channel_bar);
}

/**
 * Destroys a  channel bar and accessor instance.
 * 
 * @param   accessor        accessor pointer
 * @param   channel_bar     channel bar pointer
 */
void destroy_test_harness(sdl_channel_bar_test_access* accessor, sdl_channel_bar* channel_bar) {
    delete accessor;
    delete channel_bar;
    SDL_Quit();
}

/**
 * Tests the channel bar constructor and destructor.
 * 
 * @return  true if the test is successful
 */
bool test_sdl_channel_bar_constructor() {
    sdl_channel_bar* channel_bar;
    sdl_channel_bar_test_access* accessor;
    create_test_harness(channel_bar, accessor);
    bool test_ok = (accessor->access_vector().size() == TEST_CHANNELS_NUM)
        && (accessor->get_mutex() != NULL);
    destroy_test_harness(accessor, channel_bar);
    return test_ok;
}

/**
 * Tests the update channel method.
 * 
 * @return  true if the test is successful
 */
bool test_sdl_channel_bar_update_channel() {
    sdl_channel_bar* channel_bar;
    sdl_channel_bar_test_access* accessor;
    create_test_harness(channel_bar, accessor);
    
    // Tests effective channel update.
    for (int i = 0; i < TEST_CHANNELS_NUM; i++) {
        int val = TEST_CHANNEL_VALUES[i];
        channel_bar->update(i, val);
    }
    
    bool test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);

    // Tests mutex failure.
    if (test_ok) {
        SDL_mutex* mutex = accessor->get_mutex();
        accessor->set_mutex(NULL);
        for (int i = 0; i < TEST_CHANNELS_NUM; i++) {
            int val2 = TEST_CHANNEL_VALUES2[i];
            channel_bar->update(i, val2);
        }
        test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);
        accessor->set_mutex(mutex);
    }
    
    destroy_test_harness(accessor, channel_bar);
    return test_ok;
}

/**
 * Tests the update all channels method.
 * 
 * @return  true if the test is successful
 */
bool test_sdl_channel_bar_update_all() {
    sdl_channel_bar* channel_bar;
    sdl_channel_bar_test_access* accessor;

    create_test_harness(channel_bar, accessor);

    channel_bar->update_all(TEST_CHANNEL_VALUES);
    bool test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);
    
    // Tests mutex failure.
    if (test_ok) {
        SDL_mutex* mutex = accessor->get_mutex();
        accessor->set_mutex(NULL);
        channel_bar->update_all(TEST_CHANNEL_VALUES2);
        test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);
        accessor->set_mutex(mutex);
    }
    
    destroy_test_harness(accessor, channel_bar);
    return test_ok;
}

/**
 * Tests the reset channels method.
 * 
 * @return  true if the test is successful
 */
bool test_sdl_channel_bar_reset_channels() {
    sdl_channel_bar* channel_bar;
    sdl_channel_bar_test_access* accessor;
    create_test_harness(channel_bar, accessor);

    channel_bar->reset_channels();
    bool test_ok = check_channels(accessor, TEST_CHANNEL_ZEROES);

    // Tests mutex failure.
    if (test_ok) {
        channel_bar->update_all(TEST_CHANNEL_VALUES);
        SDL_mutex* mutex = accessor->get_mutex();
        accessor->set_mutex(NULL);
        channel_bar->reset_channels();
        test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);
        accessor->set_mutex(mutex);
    }
    
    destroy_test_harness(accessor, channel_bar);
    return test_ok;
}

/**
 * Tests the timer callback.
 * 
 * @return  true if the test is successful
 */
bool test_sdl_channel_bar_time_elapsed() {
    int interval = 10 * sdl_channel_bar::DECAY_TIMER / 100;
    sdl_channel_bar* channel_bar;
    sdl_channel_bar_test_access* accessor;
    create_test_harness(channel_bar, accessor);
    channel_bar->update_all(TEST_CHANNEL_VALUES2);
    channel_bar->time_elapsed(interval);
    bool test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);
    // Tests mutex failure.
    if (test_ok) {
        SDL_mutex* mutex = accessor->get_mutex();
        accessor->set_mutex(NULL);
        channel_bar->time_elapsed(interval);
        test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);
        accessor->set_mutex(mutex);
    }
    
    destroy_test_harness(accessor, channel_bar);
    return test_ok;
}

/**
 * Tests the get channels method.
 * 
 * @return  true if the test is successful
 */
bool test_sdl_channel_bar_get_numchannels() {
    sdl_channel_bar* channel_bar;
    sdl_channel_bar_test_access* accessor;

    create_test_harness(channel_bar, accessor);

    int num_channels = channel_bar->get_numchannels();
    bool test_ok = (num_channels == TEST_CHANNELS_NUM);
    
    // Tests mutex failure.
    if (test_ok) {
        SDL_mutex* mutex = accessor->get_mutex();
        accessor->set_mutex(NULL);
        num_channels = channel_bar->get_numchannels();
        test_ok = (num_channels == 0);
        accessor->set_mutex(mutex);
    }
    
    destroy_test_harness(accessor, channel_bar);
    return test_ok;
}

/**
 * Tests the get channels method.
 * 
 * @return  true if the test is successful
 */
bool test_sdl_channel_bar_get_channels() {
    int test_bar[8];
    sdl_channel_bar* channel_bar;
    sdl_channel_bar_test_access* accessor;

    create_test_harness(channel_bar, accessor);

    channel_bar->update_all(TEST_CHANNEL_VALUES);
    channel_bar->get_channels(test_bar);
    bool test_ok = check_channels(accessor, test_bar);
    // Tests mutex failure.
    if (test_ok) {
        SDL_mutex* mutex = accessor->get_mutex();
        accessor->set_mutex(NULL);
        channel_bar->update_all(TEST_CHANNEL_VALUES2);
        channel_bar->get_channels(test_bar);
        test_ok = check_channels(accessor, TEST_CHANNEL_VALUES);
        accessor->set_mutex(mutex);
    }
    
    destroy_test_harness(accessor, channel_bar);
    return test_ok;
}
// Loads the tests in the appropriate array.
void load_test_map(std::map<std::string, bool(*)()>& tests) {
    tests["sdl_channel_bar|sdl_channel_bar.sdl_channel_bar"] = test_sdl_channel_bar_constructor;
    tests["sdl_channel_bar|sdl_channel_bar.update_channel"] = test_sdl_channel_bar_update_channel;
    tests["sdl_channel_bar|sdl_channel_bar.update_all"] = test_sdl_channel_bar_update_all;
    tests["sdl_channel_bar|sdl_channel_bar.reset_channels"] = test_sdl_channel_bar_reset_channels;
    tests["sdl_channel_bar|sdl_channel_bar.time_elapsed"] = test_sdl_channel_bar_time_elapsed;
    tests["sdl_channel_bar|sdl_channel_bar.get_numchannels"] = test_sdl_channel_bar_get_numchannels;
    tests["sdl_channel_bar|sdl_channel_bar.get_channels"] = test_sdl_channel_bar_get_channels;
}