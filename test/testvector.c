#include <criterion/criterion.h>

#include "../src/utils/vector.h"


Test(testvector, testscale) {
    double r[] = {2, 4, 6};
    Vector R = vector_init_by_array(3, r);
    vector_scale(R, 0.5);
    cr_assert(vector_get(R, 0) == 1);
    cr_assert(vector_get(R, 1) == 2);
    cr_assert(vector_get(R, 2) == 3);
}

Test(testvector, testadd) {
    double r1[] = {2, 4, 6};
    Vector R1 = vector_init_by_array(3, r1);

    double r2[] = {0, 14, 9};
    Vector R2 = vector_init_by_array(3, r2);

    vector_add(R1, R2);
    cr_assert(vector_get(R1, 0) == 2, "%d != 2", vector_get(R1, 0));
    cr_assert(vector_get(R1, 1) == 18, "%d != 28", vector_get(R1, 1));
    cr_assert(vector_get(R1, 2) == 15, "%d != 15", vector_get(R1, 2));       
}

Test(testvector, testinitbyvalue) {
    Vector R = vector_init_by_value(3, 5.7);
    cr_assert(R->items[0] == 5.7);
    cr_assert(R->items[1] == 5.7);
    cr_assert(R->items[2] == 5.7);
}