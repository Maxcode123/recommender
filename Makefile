CC=gcc
ARGS=-g
DB=gdb
OBJ=obj
SRC=src
PREPROCESS=$(SRC)/preprocess
PARSER=$(PREPROCESS)/parser
SCANNER=$(PARSER)/scanner
PRESCANNER=$(SCANNER)/prescanner


all: obj/lex.yy.o obj/parser.o test/main.c
	$(CC) $^ -o test/bin/main

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
	$(CC) $(ARGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(PARSER)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SCANNER)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(PRESCANNER)/%.c
	$(CC) $(ARGS) -c $< -o $@

clean:
	rm -rf obj/* test/bin/* scanner prescanner src/preprocess/parser/scanner/lex.yy.c src/preprocess/parser/scanner/prescanner/prelex.yy.c data/preprocessed/*
