/*
 * sadplay - AdLib music player with graphics.
 * 
 * texts.cc - Help messages
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

#include "texts.h"

// General help
const char* texts::HELP_TEXT =
    "| Keys                           | Command                 |\n"
    "| ------------------------------ | ------------------------|\n"
    "| [Q]                            | Quits the program       |\n"
    "| [N] [RIGHT ARROW] [DOWN ARROW] | Plays the next song     |\n"
    "| [LEFT_ARROW] [UP ARROW]        | Plays the previous song |\n"
    "| [SPACE]                        | Pauses/resumes the song |\n"
    "| [C]                            | Show the license        |\n"
    "| [W]                            | Show the (no) warranty  |\n"
    "| [I]                            | Show song information   |\n"
    "| [H]                            | This help message       |\n\n";

// License
const char* texts::LICENSE_TEXT =
    "sadplay - AdLib music player with graphics.\n\n" 
    "Copyright (C) 2019 Marco Confalonieri <marco at marcoconfalonieri.it>\n\n"
    "This program is free software: you can redistribute it and/or modify\n"
    "it under the terms of the GNU General Public License as published by\n"
    "the Free Software Foundation, either version 3 of the License, or\n"
    "(at your option) any later version.\n\n";

// Warranty
const char* texts::WARRANTY_TEXT =
    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "GNU General Public License for more details.\n\n";

// Command line help
const char* texts::CMDLINE_HELP_TEXT =
    "The program **must** be called with either a list of files to play or the -f\n"
    "option followed by a text files containing the names of the files to be played\n"
    "(one per line).\n\n"
    "    sadplay [-v] [-l <logfile>] [-f <list_file>] [-r] <file1> [<file2>] [...]\n\n"
    "Follows a description of the arguments:\n\n"
    "    -v                             Turn on verbose messages\n"
    "    -l     <logfile>               Output messages to <logfile>\n"
    "    -f     <list_file>             Get the file list from <list_file>\n"
    "    -r                             Repeat the file list\n"
    "    -c                             Continuous play of each song\n"
    "           <file1> [<file2>] [...] Files to be played. With -f they are ignored\n\n";
