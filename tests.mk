TEST=test
COMPILE=$(CC) $^ -o $@ -lcriterion
MATHLIB=-lm

test-matrix: $(TEST)/bin/testmatrix
	$<

$(TEST)/bin/testmatrix: $(TEST)/testmatrix.c $(OBJ)/matrix.o $(OBJ)/vector.o
	$(COMPILE) $(MATHLIB)

test-vector: $(TEST)/bin/testvector
	$<

$(TEST)/bin/testvector: $(TEST)/testvector.c $(OBJ)/vector.o
	$(COMPILE) $(MATHLIB)

test-date: $(TEST)/bin/testdate
	$<

$(TEST)/bin/testdate: $(TEST)/testdate.c $(OBJ)/date.o
	$(COMPILE)

test-vectorization: $(TEST)/bin/testvectorization
	$<

$(TEST)/bin/testvectorization: $(TEST)/integration/testvectorization.c
$(TEST)/bin/testvectorization: $(OBJ)/lex.yy.o $(OBJ)/parser.o $(OBJ)/filter.o
$(TEST)/bin/testvectorization: $(UTILSO) $(OBJ)/vectorization.o

$(TEST)/bin/testvectorization:
	$(COMPILE) $(MATHLIB)

test-kmeans: $(TEST)/bin/testkmeans
	$<

$(TEST)/bin/testkmeans: $(TEST)/testkmeans.c $(UTILSO) $(OBJ)/kmeans.o
	$(COMPILE) $(MATHLIB)