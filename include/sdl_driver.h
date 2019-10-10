/*
 * sadplay - AdLib music player with graphics.
 * 
 * sdl_driver.h - header for SDL display driver and channel bar.
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

/**
 * SDL display driver.
 */
class sdl_display_driver : public display {
    private:
};

#endif // _SADPLAY_SDL_DRIVER_H_