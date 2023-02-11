#include "../src/preprocess/parser/parser.h"



int main(int argc, char **argv) {
    char *fname = argv[1];
    
    List rlst = lst_list();
    parseall(&rlst);

    // Map usermap = map();
    // mapusers2(ht, rlst);

    

    // mapusers(usermap, rlst);
    // printf("unique users: %d\n", map_len(usermap));

    // Map moviemap = map();
    // mapmovies(moviemap, rlst);
    // printf("unique movies: %d\n", map_len(moviemap));
}