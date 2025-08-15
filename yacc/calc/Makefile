CC = gcc
LEX = lex
YACC = yacc -d

LEX_FILE = calc.l
YACC_FILE = calc.y
LEX_OUT = lex.yy.c
YACC_OUT = y.tab.c
YACC_HEADER = y.tab.h
EXEC = calc

all : $(EXEC)
	./$(EXEC)

$(EXEC) : $(LEX_OUT) $(YACC_OUT)
	$(CC) $(LEX_OUT) $(YACC_OUT) -o $(EXEC) -lm

$(LEX_OUT) : $(LEX_FILE) $(YACC_HEADER)
	$(LEX) $(LEX_FILE)

$(YACC_OUT) $(YACC_HEADER) : $(YACC_FILE)
	$(YACC) $(YACC_FILE)

clean :
	rm -f $(LEX_OUT) $(YACC_OUT) $(YACC_HEADER) $(EXEC)
