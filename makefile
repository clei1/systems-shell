all: aesthetics parse.c
	gcc parse.c

clean: *.out *~
	rm *.out
	rm *~

run: a.out
	./a.out
