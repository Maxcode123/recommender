unique: $(OBJ)/unique.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/map.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@

ratings-histogram: $(OBJ)/ratings.o $(OBJ)/histogram.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/map.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@ 0 2 5 10 15
	gnuplot plot/ratings_per_user_histogram.txt

filtered: $(OBJ)/filtered.o $(OBJ)/filter.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/map.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@