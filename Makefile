CC=gcc
ARGS=-g
OBJCOMP=$(CC) $(ARGS) -c $< -o $@
DB=gdb
OBJ=obj
SRC=src
PREPROCESS=$(SRC)/preprocess
PARSER=$(PREPROCESS)/parser
SCANNER=$(PARSER)/scanner
PRESCANNER=$(SCANNER)/prescanner
SCRIPTS=$(SRC)/scripts

include scripts.mk

all: $(OBJ)/lex.yy.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/map.o $(OBJ)/date.o test/main.c
	$(CC) $^ -o test/bin/main

histogram: $(OBJ)/histogram.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/map.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@

run-file: all
	test/bin/main data/preprocessed/Troy\ 2004.csv

debug: all
	$(DB) test/bin/main

debug-file: all
	$(DB) --args test/bin/main data/preprocessed/Troy\ 2004.csv

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

$(OBJ)/%.o: $(SRC)/utils/%.c
	$(OBJCOMP)

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


clean-preprocessed:
	rm -r data/preprocessed/*

clean:
	rm -rf obj/* test/bin/* histogram unique scanner prescanner src/preprocess/parser/scanner/lex.yy.c src/preprocess/parser/scanner/prescanner/prelex.yy.c
