#!/bin/sh

export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH

CURR_DIR=$(dirname $0)
echo $(cat data/config/local)
./bin/sdl_minimal_executable $(cat data/config/local)
