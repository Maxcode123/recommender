#include "map.h"

Map map() {
    Map m = malloc(sizeof(*m));
    m->lst = lst_list();
    return m;
}

bool map_put(Map m, key k, MapItem i) {
    Node n;
    if (n = lst_get(k, m->lst)) {
        MapItem tmp = n->i;
        n->i = i;
        free(tmp);
        return false;
    }
    lst_add(node(k, i), &m->lst);
    return true;
}

MapItem map_get(Map m, key k) {
    Node n;
    if (n = lst_get(k, m->lst)) return n->i;
    return NULL;
}

int map_len(Map m) {
    return lst_len(m->lst);
}

void map_clear(Map m) {
    lst_clear(&m->lst);
}