#!/bin/bash

CFLAGS="-I. -Wall -Wextra -Werror -std=c11 -pedantic `sdl2-config --libs` -lGL -lm -O3 -g"

gcc main.c renderer.c microui.c $CFLAGS

