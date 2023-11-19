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

# -n flag will generate symbols for easier debugging process
rgblink "$base.o" -n "$base.sym" -o "$base.gb"

# These two flags will essentially always be used
# -v produce a valid ROM header
# -p pad ROM to the next valid size using $FF as the filler byte, then writes
# the appopriate value to the ROM size byte
rgbfix -v -p 0xFF "$base.gb"

