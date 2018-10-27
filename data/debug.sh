#!/bin/sh

CURR_DIR=$(dirname $0)

gdb --args ./bin/sdlminimal $(cat data/config/local)
