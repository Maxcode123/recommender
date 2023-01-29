#include <criterion/criterion.h>

#include "../src/utils/list.h"
#include "../src/utils/map.h"


Test(testmap, testput) {
    Map m = map();
    int *i1 = malloc(sizeof(int));
    *i1 = 5;
    cr_assert(map_put(m, "key1", i1));
    cr_assert(m->lst->i == i1);
    cr_assert(strcmp(m->lst->k, "key1") == 0);

    int *i2 = malloc(sizeof(int));
    *i2 = 15;
    cr_assert(map_put(m, "key2", i2));
    cr_assert(m->lst->i == i2);
    cr_assert(strcmp(m->lst->k, "key2") == 0);

    cr_assert(!map_put(m, "key2", i1));
    cr_assert(m->lst->i == i1);

    Map m2 = map();
    cr_assert(map_put(m2, "map", m));
    cr_assert(m2->lst->i == m);
}

Test(testmap, testget) {
    Map m = map();
    int *i1 = malloc(sizeof(int));
    *i1 = 5;
    int *i2 = malloc(sizeof(int));
    *i2 = 20;
    lst_add(node("key1", i1), &m->lst);
    lst_add(node("key2", i2), &m->lst);
    cr_assert(map_get(m, "key1") == i1);
    cr_assert(map_get(m, "key2") == i2);   
    cr_assert(map_get(m, "key3") == NULL); 
}

Test(testmap, testlen) {
    Map m = map();
    cr_assert(map_len(m) == 0);
    lst_add(node("a", NULL), &m->lst);
    cr_assert(map_len(m) == 1);
    lst_add(node("b", NULL), &m->lst);
    cr_assert(map_len(m) == 2);
}

Test(testmap, testclear) {
    Map m = map();
    lst_add(node("a", NULL), &m->lst);
    lst_add(node("b", NULL), &m->lst);
    lst_add(node("c", NULL), &m->lst);
    map_clear(m);
    cr_assert(m->lst == NULL);
}