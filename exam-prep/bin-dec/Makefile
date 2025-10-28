all: a.out
	./a.out

a.out: lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c

lex.yy.c: lex.l y.tab.h
	flex lex.l

y.tab.c y.tab.h: yacc.y
	yacc -d yacc.y

clean:
	rm -f *.out *.yy.c | true
