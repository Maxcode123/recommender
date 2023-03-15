#include "matrix.h"

Vector *matrix(HashTable usermap, HashTable moviemap) {
    Vector *m = malloc(sizeof(*m) * ht_size(usermap));
    Iterator u_it = ht_it(usermap);
    Node n;
    int i = 0;
    while (ht_next(u_it)) {
        Vector v = vector_create(ht_size(moviemap));
        List lst = u_it->value;
        int c = 0;
        Iterator m_it = ht_it(moviemap);
        while (ht_next(m_it)) {
            if (n = lst_get(m_it->key, lst)) vector_set(v, c++, ((Rating)n->i)->value);
            else vector_set(v, c++, 0);
        }
        m[i++] = v;
    }
    return m;
}