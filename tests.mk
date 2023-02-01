CC=gcc
ARGS=-g
OBJ=obj
TEST=test
SRC=src
PREPROCESS=$(SRC)/preprocess
PARSER=$(PREPROCESS)/parser
SCANNER=$(PARSER)/scanner
PRESCANNER=$(SCANNER)/prescanner


test-map: $(TEST)/bin/testmap
	$<

$(TEST)/bin/testmap: $(TEST)/testmap.c $(OBJ)/list.o $(OBJ)/map.o
	$(CC) $^ -o $@ -lcriterion

test-date: $(TEST)/bin/testdate
	$<

$(TEST)/bin/testdate: $(TEST)/testdate.c $(OBJ)/parser.o $(OBJ)/lex.yy.o $(OBJ)/list.o $(OBJ)/map.o
	$(CC) $^ -o $@ -lcriterion