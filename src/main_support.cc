/*
 * sadplay - AdLib music player with graphics.
 * 
 * main_support.cc - implementation of the support functions for main.
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

#include "main_support.h"

#include <fstream>
#include <iostream>

#include <unistd.h>

using std::ifstream;
using std::string;

// Reads the file list from a text file or the standard input.
void read_file_list_from_file(sadplay_args* args, string file, std::istream &input) {
    std::istream* file_list;

    // Open a file or assign our stream to standard input.
    if (file == "-") {
        file_list = &input;
    } else {
        file_list = new ifstream(file);
    }

    // Read the stream line by line.
    string line;
    while (std::getline(*file_list, line)) {
        args->file_list.push_back(line);
    }

    // if the file list is not in the standard input, closes the stream and
    // delete it. 
    if (file_list != &input) {
        ((ifstream*) file_list)->close();
        delete file_list;
        file_list = NULL;
    }
}

// Reads the file list from the command line arguments.
void read_file_list_from_argv(sadplay_args* args, int argc, char* argv[], int opt_index) {
    for (int idx = opt_index; idx < argc; idx++) {
        args->file_list.push_back(string(argv[idx]));
    }
}

// Reads the command line arguments.
void read_command_line(sadplay_args* args, int argc, char* argv[]) {
    int c;
    string file;
    bool file_list_used = false;
    while ((c = getopt(argc, argv, "scvl:f:r")) != -1) {
        switch (c) {
            case 'v':
                args->verbose = true;
                break;
            case 'l':
                args->log_file = string(optarg);
                 break;
            case 'f':
                file = string(optarg);
                file_list_used = true;
                break;
            case 'r':
                args->repeat = true;
                break;
            case 'c':
                args->continuous = true;
                break;
            case 's':
                args->shuffle = true;
                break;
            case '?':
                args->error = true;
                return;
        }
    }

    // Either read the file list from a file or from the command line.
    if (file_list_used) {
        read_file_list_from_file(args, file);
    } else {
        read_file_list_from_argv(args, argc, argv, optind);
    }
}
