TEST=test
COMPILE=$(CC) $^ -o $@ -lcriterion

test-date: $(TEST)/bin/testdate
	$<

$(TEST)/bin/testdate: $(TEST)/testdate.c $(OBJ)/date.o
	$(COMPILE)

test-matrix: $(TEST)/bin/testmatrix
	$<

$(TEST)/bin/testmatrix: $(TEST)/integration/testmatrix.c $(OBJ)/lex.yy.o $(OBJ)/parser.o
$(TEST)/bin/testmatrix: $(OBJ)/filter.o $(OBJ)/vector.o $(OBJ)/hashset.o $(OBJ)/list.o $(OBJ)/date.o

$(TEST)/bin/testmatrix:
	$(COMPILE) -lm
