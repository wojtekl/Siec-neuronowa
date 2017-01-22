#!/bin/bash

wynik=$(echo $1 | sed -e "s/\..*//")
gcc $1 -ansi -lm -o $wynik
