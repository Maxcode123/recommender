CC=gcc
OBJ=obj
TEST=test
COMPILE=$(CC) $^ -o $@ -lcriterion

test-map: $(TEST)/bin/testmap
	$<

$(TEST)/bin/testmap: $(TEST)/testmap.c $(OBJ)/list.o $(OBJ)/map.o
	$(COMPILE)

test-date: $(TEST)/bin/testdate
	$<

$(TEST)/bin/testdate: $(TEST)/testdate.c $(OBJ)/parser.o $(OBJ)/lex.yy.o $(OBJ)/list.o $(OBJ)/map.o
	$(COMPILE)