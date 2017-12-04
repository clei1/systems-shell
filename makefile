all: aesthetics shell.h shell.c
	gcc shell.c

clean: *.out
	rm *.out

run: a.out
	./a.out
