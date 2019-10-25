[![Build Status](https://dev.azure.com/mconfalonieri/sadplay/_apis/build/status/sadplay-latest?branchName=master)](https://dev.azure.com/mconfalonieri/sadplay/_build/latest?definitionId=1&branchName=master)

# sadplay

Sadplay is a simple, old-school AdLib player that uses the
[AdPlug](http://adplug.github.io/) library to play music,
[FFTW](http://www.fftw.org/) to analyze its spectrum, and
[SDL2](https://www.libsdl.org/) to show the result in a nice way.

In case you are sad and have nostalgia of the old times, you can play your
favorite Adlib tunes and release your sadness.

## Invoking the command line
The program **must** be called with either a list of files to play or the `-f`
option followed by a text files containing the names of the files to be played
(one per line).

```bash
sadplay [-v] [-l <logfile>] [-f <list_file>] [-r] <file1> [<file2>] [...]
```

Follows a description of the arguments:

| Switch | Argument      | Description                                      |
| ------ | ------------- | ------------------------------------------------ |
| `-v`   |               | Turn on verbose messages                         |
| `-l`   | `<logfile>`   | Output messages to `<logfile>`                   |
| `-f`   | `<list_file>` | Get the file list from `<list_file>`             |
| `-r`   |               | Repeat the file list                             |
| `-c`   |               | Continuous play of each song (until interruptes) |
| `-s`   |               | Shuffles the playlist before playing it          |
|        | `<file1>`     | Files to be played. With `-f` they are ignored   |

## Commands during execution
The following keys can be used to control sadplay during the execution.

| Keys                           | Command                 |
| ------------------------------ | ------------------------|
| `q`                            | Quits the program       |
| `n` `RIGHT ARROW` `DOWN ARROW` | Plays the next song     |
| `LEFT_ARROW` `UP ARROW`        | Plays the previous song |
| `SPACE`                        | Pauses/resumes the song |
| `C`                            | Show the license        |
| `W`                            | Show the (no) warranty  |
| `I`                            | Show song information   |
| `H`                            | Get help on commands    |

## Compilation
The compilation has been tested on Ubuntu 18.04.3 LTS and on MacOS X (I don't
remember which version).

### Prerequisites
The following libraries should be installed, with their headers:
 
 * [AdPlug v2](http://adplug.github.io/);
 * [FFTW v3](http://www.fftw.org/): also the `fftw-mpi` module is required;
 * [SDL2](https://www.libsdl.org/).

### Compilation
The sources can be configured using the "standard" autoconf/automake magic:

```bash
./configure
```

And running make:

```bash
make
```

The following step _could_ need superuser privileges to install the executable
in `/usr/local/bin`:

```bash
make install
```


## Binary packages
No binary packages at this time. Maybe in the future, in the meantime you can
compile from the sources and feel even more nostalgic. :-)

## Authors
Right now I (Marco Confalonieri) am the only developer. Many thanks to the
authors of the wonderful libraries that allowed me to write this little piece
of code with just a fraction of the effort that I would have needed to write
everything from scratch.

## Credits
The routine for feeding the SDL audio buffer is shamelessly taken from the
UNIX version of [AdPlay](https://github.com/adplug/adplay-unix). I believe the
authors are Simon Peter and Mike Gorchak.
