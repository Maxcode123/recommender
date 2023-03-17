#include "filter.h"

void filter(HashTable *usermap, List *rlst) {
    List fltr = lst_list();
    HashTable fltrmap = ht_init(ht_size(*usermap));
    
    List lst;
    int len;
    Iterator it = ht_it(*usermap);
    while (ht_next(it)) {
        lst = (List)(it->value);
        len = lst_len(lst);
        if (len < RMIN || len > RMAX || len == 0) {
            continue;
        }
        ht_insert(fltrmap, it->key, it->value);
        while (lst != NULL) {
            lst_add(node(lst->k, lst->i), &fltr);
            lst = lst->next;
        }
    }
    
    HashTable tmp = *usermap;
    *usermap = fltrmap;
    free(tmp);

    List tmp2 = *rlst;
    *rlst = fltr;
    free(tmp2);
}
