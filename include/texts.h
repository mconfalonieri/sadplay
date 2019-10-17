/*
 * sadplay - AdLib music player with graphics.
 * 
 * texts.h - Header for help messages.
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

#ifndef _SADPLAY_TEXTS_H_
#define _SADPLAY_TEXTS_H_

/**
 * Utility class that contains useful long texts.
 */
class texts {
    public:
    /**
    * Help text.
    */
    const static char* HELP_TEXT;

    /**
     * License text.
     */
    const static char* LICENSE_TEXT;

    /**
     * Warranty text.
     */
    const static char* WARRANTY_TEXT;

    /**
     * Help on command line options.
     */
    const static char* CMDLINE_HELP_TEXT;
};

#endif // _SADPLAY_TEXTS_H_
