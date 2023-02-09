#include "filter.h"

void filter(Map usermap) {
    List tmp = usermap->lst;
    List rlst;
    int len;
    while (tmp != NULL) {
        rlst = (List)tmp->i;
        len = lst_len(rlst);
        if (len < RMIN || len > RMAX) map_del(usermap, tmp->k);
        tmp = tmp->next;
    }
}