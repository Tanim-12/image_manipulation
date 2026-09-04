#!/bin/bash
# IUP build & run script (multi-file version)
# Usage: ./build.sh [output_name]
# Example: ./build.sh imageeditor

OUT="${1:-imageeditor}"

IUP_INCLUDE=~/iup/iup/include
IUP_LIB=~/iup/iup/lib/MacOS265

SRCS="main.c gui.c image.c processing.c"

for f in $SRCS; do
  if [ ! -f "$f" ]; then
    echo "Error: $f not found in current folder."
    exit 1
  fi
done

echo "Compiling $SRCS ..."
clang $SRCS -o "$OUT" -I "$IUP_INCLUDE" -L "$IUP_LIB" -liup

if [ $? -ne 0 ]; then
  echo "Compilation failed."
  exit 1
fi

install_name_tool -change libiup.dylib "$IUP_LIB/libiup.dylib" "./$OUT"

echo "Running $OUT ..."
"./$OUT"
