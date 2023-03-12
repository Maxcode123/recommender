#include "filter.h"

List filter(HashTable usermap, List rlst) {
    List lst;
    int len;
    List fltr = lst_list();
    for (int i = 0; i < ht_size(usermap); i++) {
        lst = (List)(usermap->entries[i].value);
        len = lst_len(lst);
        if (len == 0) continue;
        if (len < RMIN || len > RMAX) {
            ht_delete(usermap, usermap->entries[i].key);
            continue;
        }
        while (lst != NULL) {
            lst_add(node(lst->k, lst->i), &fltr);
            lst = lst->next;
        }
    }
    return fltr;
}
