#!/bin/sh
bison -d cparse.y
flex cparse.l
gcc -o cparse lex.yy.c -lfl -lm
