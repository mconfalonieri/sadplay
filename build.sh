#!/bin/sh
automake --add-missing && autoconf
./configure
make
