/*
 * sadplay - AdLib music player with graphics.
 * 
 * main_support.h - headers of the support functions for main.
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
#ifndef _SADPLAY_MAIN_SUPPORT_H_
#define _SADPLAY_MAIN_SUPPORT_H_

#include <iostream>
#include <string>

#include "sadplay.h"

/**
 * Reads the audio file list from a file. The special argument '-' can be used
 * for reading the list from the standard input. The list is read as one file
 * per line.
 * 
 * @param   args                    the sadplay_args variable to fill.
 * @param   file                    the file list file
 * @param   input                   the input stream to use as stdin
 */
void read_file_list_from_file(sadplay_args* args, std::string file,
        std::istream &input = std::cin);

/**
 * Reads the audio file list from the command line vector.
 * 
 * @param   args                    the sadplay_args variable.
 * @param   argc                    number of command line arguments
 * @param   argv                    array of command line arguments
 * @param   index                   the index to start reading from.
 */
void read_file_list_from_argv(sadplay_args* args, int argc, char* argv[], int index);

/**
 * Reads the command line options. This function reads the command line
 * arguments and parses them into the sadplay_args structure provided.
 * 
 * @param   args                    the sadplay_args variable
 * @param   argc                    number of command line arguments
 * @param   argv                    array of command line arguments
 */
void read_command_line(sadplay_args* args, int argc, char* argv[]);

#endif // _SADPLAY_MAIN_SUPPORT_H_