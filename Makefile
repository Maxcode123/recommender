CC=gcc
ARGS=-g
DB=gdb
OBJ=obj
SRC=src
PREPROCESS=$(SRC)/preprocess
PARSER=$(PREPROCESS)/parser
SCANNER=$(PARSER)/scanner
PRESCANNER=$(SCANNER)/prescanner


all: $(OBJ)/lex.yy.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/map.o $(OBJ)/date.o test/main.c
	$(CC) $^ -o test/bin/main

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
	$(CC) $(ARGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/utils/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(PREPROCESS)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(PARSER)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SCANNER)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(PRESCANNER)/%.c
	$(CC) $(ARGS) -c $< -o $@

clean-preprocessed:
	rm -r data/preprocessed/*

clean:
	rm -rf obj/* test/bin/* histogram scanner prescanner src/preprocess/parser/scanner/lex.yy.c src/preprocess/parser/scanner/prescanner/prelex.yy.c
