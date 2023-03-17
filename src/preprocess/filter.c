#include "filter.h"

List filter(HashTable usermap, List rlst) {
    List lst;
    int len;
    List fltr = lst_list();
    Iterator it = ht_it(usermap);
    while (ht_next(it)) {
        lst = (List)(it->value);
        len = lst_len(lst);
        if (len == 0) continue;
        if (len < RMIN || len > RMAX) {
            ht_delete(usermap, it->key);
            continue;
        }
        while (lst != NULL) {
            lst_add(node(lst->k, lst->i), &fltr);
            lst = lst->next;
        }
    }
    return fltr;
}
