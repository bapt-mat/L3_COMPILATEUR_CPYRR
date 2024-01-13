CC = gcc

YACC = yacc
YFLAGS = -v -d
LEX = lex

LIBS = -ll

SRC = y.tab.c lex.yy.c

OBJ = lex.yy.o

OUT = compilateur

all :	$(OUT)

$(OUT) : $(SRC) $(OBJ)
	$(CC) $(SRC) -o $(OUT) $(LIBS)

lex.yy.c : $(OUT).l
	$(LEX) $(OUT).l

y.tab.c : $(OUT).y
	$(YACC) $(YFLAGS) $(OUT).y

lex.yy.o : lex.yy.c
	$(CC) -c lex.yy.c

clean :
	rm -f $(OUT) $(SRC) $(OBJ) y.output y.tab.h

