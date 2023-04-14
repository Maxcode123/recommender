predict: $(OBJ)/predict_ratings.o $(OBJ)/filter.o $(OBJ)/parser.o $(UTILSO) $(OBJ)/lex.yy.o $(OBJ)/vectorization.o $(OBJ)/kmeans.o
	$(CC) $^ -o $@ -lm
	clear

scatter: $(OBJ)/scatter.o $(OBJ)/filter.o $(OBJ)/parser.o $(UTILSO) $(OBJ)/PCA.o $(OBJ)/lex.yy.o $(OBJ)/vectorization.o
	$(CC) $^ -o $@ -lm
	clear

unique: $(OBJ)/unique.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@

unique-filtered: $(OBJ)/unique_filtered.o $(OBJ)/filter.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@

ratings: $(OBJ)/ratings.o $(OBJ)/histogram.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@ 0 20 40 60 80
	gnuplot plot/ratings_per_user_histogram.txt
	code plot/ratings_per_user.jpg

ratings-filtered: $(OBJ)/ratings_filtered.o $(OBJ)/filter.o $(OBJ)/histogram.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@ 10 20 30 40 45
	gnuplot plot/ratings_per_user_histogram.txt
	code plot/ratings_per_user.jpg

dates: $(OBJ)/dates_filtered.o $(OBJ)/filter.o $(OBJ)/histogram.o $(OBJ)/parser.o $(OBJ)/list.o $(OBJ)/hashset.o $(OBJ)/date.o $(OBJ)/lex.yy.o
	$(CC) $^ -o $@
	clear
	./$@ 0 365 730 1095
	gnuplot plot/ratings_per_date_period_histogram.txt
	code plot/date_periods.jpg