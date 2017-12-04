all: aesthetics headers.h shell.c command.c parse.c redirect.c spoon.c
	gcc shell.c

clean: *.out
	rm *.out

run: a.out
	./a.out
