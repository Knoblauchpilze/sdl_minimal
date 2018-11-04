#!/bin/sh

CURR_DIR=$(dirname $0)

gdb --args ./bin/sdl_minimal_executable $(cat data/config/local)
