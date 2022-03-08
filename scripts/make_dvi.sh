#!/usr/bin/bash

find . -type f -name "*.tex" | xargs -0 texi2dvi 