CC = gcc
LEX = lex

LEX_FILE = lex.l
LEX_OUT = lex.yy.c
EXEC = lex

all : $(EXEC)
	./$(EXEC)

$(EXEC) : $(LEX_OUT) 
	$(CC) $(LEX_OUT) $(YACC_OUT) -o $(EXEC) -lm

$(LEX_OUT) : $(LEX_FILE) 
	$(LEX) $(LEX_FILE)


clean :
	rm -f $(LEX_OUT) $(EXEC)
