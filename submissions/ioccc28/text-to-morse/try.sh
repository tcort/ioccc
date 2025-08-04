#!/usr/bin/env bash
#
# try.sh - demonstrate IOCCC entry 2025/tcort
#          version 1.0.0

# make sure CC is set so that when we do make CC="$CC" it isn't empty. Doing it
# this way allows us to have the user specify a different compiler in an easy
# way.
[[ -z "$CC" ]] && CC="cc"

make CC="$CC" all >/dev/null || exit 1

# clear screen after compilation so that only the entry is shown
clear

read -r -n 1 -p "Press any key to run: ./prog: "
echo 1>&2
echo "Hello, IOCCC." > hello.txt
./prog hello.txt hello.wav
