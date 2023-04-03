CC=gcc
ARGS=-g
OBJCOMP=$(CC) $(ARGS) -c $< -o $@
DB=gdb
OBJ=obj
SRC=src
UTILS=$(SRC)/utils
NEURON=$(SRC)/neuron
CLUSTERING=$(SRC)/clustering
PREPROCESS=$(SRC)/preprocess
PARSER=$(PREPROCESS)/parser
SCANNER=$(PARSER)/scanner
PRESCANNER=$(SCANNER)/prescanner
SCRIPTS=$(SRC)/scripts
UTILSO=$(OBJ)/date.o $(OBJ)/vector.o $(OBJ)/hashset.o $(OBJ)/list.o $(OBJ)/matrix.o
THREADLIB=-lpthread

include scripts.mk
include tests.mk

all: $(OBJ)/lex.yy.o $(OBJ)/train.o $(OBJ)/neuron.o $(OBJ)/vectorization.o $(OBJ)/kmeans.o $(OBJ)/parser.o $(OBJ)/filter.o $(OBJ)/matrix.o $(OBJ)/PCA.o $(UTILSO) test/main.c
	$(CC) $^ -o test/bin/main -lm

debug: all
	$(DB) test/bin/main

$(SCANNER)/lex.yy.c: $(SCANNER)/scanner.lex
	lex -o $@ $<

$(PRESCANNER)/prelex.yy.c: $(PRESCANNER)/prescanner.lex
	lex -o $@ $<

pre-process: prescanner
	./$<

prescanner: obj/lexdriver.o obj/prelex.yy.o obj/preprocessor.o
	$(OBJCOMP)

$(OBJ)/%.o: $(SRC)/%.c
	$(OBJCOMP)

$(OBJ)/%.o: $(UTILS)/%.c
	$(OBJCOMP) $(THREADLIB)

$(OBJ)/%.o: $(PREPROCESS)/%.c
	$(OBJCOMP)

$(OBJ)/%.o: $(PARSER)/%.c
	$(OBJCOMP)

$(OBJ)/%.o: $(SCANNER)/%.c
	$(OBJCOMP)

$(OBJ)/%.o: $(PRESCANNER)/%.c
	$(OBJCOMP)

$(OBJ)/%.o: $(SCRIPTS)/%.c
	$(OBJCOMP)

$(OBJ)/%.o: $(CLUSTERING)/%.c
	$(OBJCOMP)

$(OBJ)/%.o: $(NEURON)/%.c
	$(OBJCOMP)


clean-preprocessed:
	rm -r data/preprocessed/*

clean:
	rm -rf obj/* test/bin/* dates ratings filtered ratings-filtered unique-filtered \
	unique scanner prescanner src/preprocess/parser/scanner/lex.yy.c \
	src/preprocess/parser/scanner/prescanner/prelex.yy.c plot/ratings_per_user.txt \
	plot/dates.txt
