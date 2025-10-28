all: a.out
	./a.out

a.out: lex.yy.c
	gcc lex.yy.c

lex.yy.c: lex.l
	flex lex.l

clean:
	rm -f *.out *.yy.c | true
