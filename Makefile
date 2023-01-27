CC=gcc
DB=gdb
OBJ=obj
SRC=src
SCANNER=$(SRC)/parser/scanner
PRESCANNER=$(SCANNER)/prescanner

debug: prescanner
	$(DB) $<

$(SCANNER)/lex.yy.c: $(SCANNER)/scanner.lex
	lex -o $@ $<

scanner: obj/lexdriver.o obj/lex.yy.o
	$(CC) $^ -o $@

$(PRESCANNER)/prelex.yy.c: $(PRESCANNER)/prescanner.lex
	lex -o $@ $<

prescanner: obj/lexdriver.o obj/prelex.yy.o obj/preprocessor.o
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@

$(OBJ)/%.o: $(SCANNER)/%.c
	$(CC) -c $< -o $@

$(OBJ)/%.o: $(PRESCANNER)/%.c
	$(CC) -c $< -o $@

clean:
	rm -rf obj/* test/bin/* scanner prescanner src/parser/scanner/lex.yy.c src/parser/scanner/prescanner/prelex.yy.c data/preprocessed/*
