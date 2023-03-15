TEST=test
COMPILE=$(CC) $^ -o $@ -lcriterion
MATHLIB=-lm

test-date: $(TEST)/bin/testdate
	$<

$(TEST)/bin/testdate: $(TEST)/testdate.c $(OBJ)/date.o
	$(COMPILE)

test-matrix: $(TEST)/bin/testmatrix
	$<

$(TEST)/bin/testmatrix: $(TEST)/integration/testmatrix.c $(OBJ)/lex.yy.o $(OBJ)/parser.o
$(TEST)/bin/testmatrix: $(OBJ)/filter.o $(OBJ)/matrix.o
$(TEST)/bin/testmatrix: $(UTILSO)

$(TEST)/bin/testmatrix:
	$(COMPILE) $(MATHLIB)

test-kmeans: $(TEST)/bin/testkmeans
	$<

$(TEST)/bin/testkmeans: $(TEST)/integration/testkmeans.c $(UTILSO) $(OBJ)/kmeans.o
	$(COMPILE) $(MATHLIB)