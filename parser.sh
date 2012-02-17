#!/bin/sh
./lemon cparse.y
flex cparse.l
gcc -c -o lex.o lex.yy.c -lm
gcc -c -o cparse.o cparse.c
gcc -c -o tree.o tree.c
gcc -c -o main.o main.c
gcc -o cparse main.o tree.o cparse.o lex.o -lm
