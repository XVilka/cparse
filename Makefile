CFLAGS=-g -ggdb -Wall

all: cparse

cparse.c: cparse.l
	./lemon cparse.y

lex.yy.c: cparse.l
	flex cparse.l

lex.yy.o: lex.yy.c

cparse.o: cparse.c
	${CC} ${CFLAGS} -c cparse.c

OBJS=cparse.o lex.yy.o tree.o main.o

cparse: lemon ${OBJS}
	${CC} ${OBJS} -o cparse

lemon:
	${CC} lemon.c -o lemon

clean:
	rm -f ${OBJS} lemon cparse lex.yy.o lex.yy.c cparse.c cparse.out cparse.h
