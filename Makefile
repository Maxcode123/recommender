CC=gcc
OBJ=obj
SRC=src

src/lex.yy.c: $(SRC)/scanner/csv.lex
	lex -o $@ $<

scanner: obj/lexdriver.o obj/lex.yy.o
	$(CC) $^ -o $@

src/scanner/prescanner/prelex.yy.c: $(SRC)/scanner/prescanner/precsv.lex
	lex -o $@ $<

prescanner: obj/lexdriver.o obj/prelex.yy.o
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@

$(OBJ)/%.o: $(SRC)/scanner/%.c
	$(CC) -c $< -o $@

$(OBJ)/%.o: $(SRC)/scanner/prescanner/%.c
	$(CC) -c $< -o $@

clean:
	rm -rf obj/* test/bin/* scanner prescanner src/scanner/lex.yy.c src/scanner/prescanner/prelex.yy.c
