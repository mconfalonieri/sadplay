/*
 * sadplay - AdLib music player with graphics.
 * 
 * sdl_driver.h - header for SDL display driver.
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
#ifndef _SADPLAY_SDL_DRIVER_H_
#define _SADPLAY_SDL_DRIVER_H_


#include <vector>

#include <SDL.h>

#include "display.h"
#include "sdl_channel_bar.h"
#include "adplug_player.h"
#include "spectrum_analyzer.h"

/**
 * Function that must be called by the SDL timer to update the channel bar.
 * 
 * @param   time_elapsed    time elapsed since last update in milliseconds
 * @param   param           the channel bar that needs to be updated
 * 
 * @return  if 0 is returned, the timer is cancelled.
 */
extern "C" Uint32 sdl_channel_bar_callback(Uint32 time_elapsed, void* param);

/**
 * SDL display driver.
 */
class sdl_display_driver : public display {
    public:
        /**
         * Screen width.
         */
        const static int SCREEN_WIDTH = 800;

        /**
         * Screen height.
         */
        const static int SCREEN_HEIGHT = 400;

        /**
         * Screen border.
         */
        const static int BORDER = 20;

        /**
         * Time interval.
         */
        const static Uint32 TIMER_INTERVAL = 20U;

        /**
         * Constructor.
         */
        sdl_display_driver();

        /**
         * Destructor.
         */
        virtual ~sdl_display_driver();

        /**
         * Initializes the view.
         * 
         * @param   num_channels    the number of channels.
         *
         * @return  true if correctly initialized
         */
        bool initialize(int num_channels);

        /**
         * Plays an audio file.
         * 
         * @param   player          the adplug player
         * 
         * @return  true if the player was started
         */
        bool play(adplug_player* player);

        /**
         * Pauses the current song.
         */
        void pause();

        /**
         * Resumes the current song.
         */
        void cont();

        /**
         * Stops the current song.
         */
        void stop();
        
        /**
         * Updates the channel bar.
         */
        void update_channel_bar();

        /**
         * Returns the channel bar instance.
         * 
         * @return  the channel bar
         */
        channel_bar* get_channel_bar();

        /**
         * Renders the scene.
         */
        void render();

    protected:
        /**
         * Internal color type.
         */
        typedef struct {
            /**
             * Red component.
             */
            Uint8 r;

            /**
             * Green component.
             */
            Uint8 g;

            /**
             * Blue component.
             */
            Uint8 b;
        } rgb;

        /**
         * Initializes the colors table.
         */
        void prepare_colors_table();

        /**
         * Normalizes colors in the standard range.
         * 
         * @param   color               reference to the color
         * @param   r                   red component
         * @param   g                   green component
         * @param   b                   blue component
         */
        void normalize_color(rgb &color, int r, int g, int b);

        /**
         * Lowers the channel bar. It is called by the callback.
         * 
         * @param   time_elapsed        the time elapsed since the last update
         *                              in milliseconds
         */
        void update_channel_bar(Uint32 time_elapsed);

        /**
         * Draws a bar at the given position.
         * 
         * @param   x                   X coordinate
         * @param   width               width of the bar
         * @param   level               bar level in percentage
         */
        void draw_bar(int x, int width, int level);

        /**
         * Calculates the color given the level.
         * 
         * @param   color               reference to the color variable
         * @param   level               bar level in percentage
         */
        void calculate_color(rgb &color, int level);

        /**
         * Draws the bars.
         */
        void draw_bars();

        /**
         * Prepare the rectangle.
         */
        void prepare_rectangle(SDL_Rect &rect, int x, int y, int w, int h);

        /**
         * Sets up audio specs.
         */
        void setup_audio_spec(SDL_AudioSpec &spec);

        /**
         * Callback for audio.
         * 
         * @param   param           user-defined parameter
         * @param   audiobuf        audio buffer
         * @param   len             length of the audio buffer
         */
        static void audio_callback(void* param, Uint8* audiobuf, int len);

        /**
         * Closes the audio device.
         */
        void close_audio_device();

    private:

        /**
         * Horizontal span.
         */
        const static int H_SPAN = (SCREEN_WIDTH - (2 * BORDER));

        /**
         * Ticks since the last channel bar update.
         */
        Uint32 last_update_ticks;

        /**
         * Mutex for on-screen operations.
         */
        SDL_mutex* mutex;

        /**
         * Time rID for the player.
         */
        SDL_TimerID timer_player;

        /**
         * SDL Window.
         */
        SDL_Window* window;

        /**
         * Renderer for the window.
         */
        SDL_Renderer* renderer;

        /**
         * Internal channel bar.
         */
        sdl_channel_bar* cbar;

        /**
         * Precalculated colors.
         */
        rgb* colors_table;

        /**
         * RGB black color.
         */
        const static rgb BLACK;

        /**
         * The "wanted" specification.
         */
        SDL_AudioSpec spec;

        /**
         * The frequency bar used for the spectrum analyzer.
         */
        frequency_bar* freq_bar;

        /**
         * The spectrum analyzer.
         */
        spectrum_analyzer* analyzer;

        /**
         * The AdPlug player instance.
         */
        adplug_player* player;

        /**
         * Audio device ID.
         */
        SDL_AudioDeviceID audio_dev_id;

        /**
         * Channel percentages.
         */
        int* channels;
};

#endif // _SADPLAY_SDL_DRIVER_H_