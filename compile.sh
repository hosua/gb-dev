#!/usr/bin/bash

FILE="$1"

if [ -z "$FILE" ]; then
	echo "Error: Script requires input file as argument!"
	exit 1
fi

base=$(basename -- "$FILE")
ext="${base##*.}"
base="${base%.*}"

rgbasm -L "$FILE" -o "$base.o"
rgblink "$base.o" -o "$base.gb"
rgbfix -v -p 0xFF "$base.gb"

