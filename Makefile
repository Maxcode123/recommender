CC=gcc
ARGS=-g
DB=gdb
OBJ=obj
SRC=src
PARSER=$(SRC)/parser
SCANNER=$(PARSER)/scanner
PRESCANNER=$(SCANNER)/prescanner


all: obj/lex.yy.o obj/parser.o test/main.c
	$(CC) $^ -o test/bin/main

debug: all
	$(DB) test/bin/main

$(SCANNER)/lex.yy.c: $(SCANNER)/scanner.lex
	lex -o $@ $<

scanner: obj/lex.yy.o obj/parser.o 
	$(CC) $^ -o $@

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
	rm -rf obj/* test/bin/* scanner prescanner src/parser/scanner/lex.yy.c src/parser/scanner/prescanner/prelex.yy.c data/preprocessed/*
