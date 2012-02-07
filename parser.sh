#!/bin/sh
lemon cparse.y
flex cparse.l
gcc -o cparse cparse.c -lfl -lm
