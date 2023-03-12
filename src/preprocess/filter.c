#include "filter.h"

void filter(HashTable usermap) {
    List rlst;
    int len;
    for (int i = 0; i < ht_size(usermap); i++) {
        rlst = (List)(usermap->entries[i].value);
        len = lst_len(rlst);
        if (len == 0) continue;;
        if (len < RMIN || len > RMAX) ht_delete(usermap, usermap->entries[i].key);
    }
}
