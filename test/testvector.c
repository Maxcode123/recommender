#include <criterion/criterion.h>

#include "../src/utils/vector.h"


Test(testvector, testscale) {
    int r[] = {2, 4, 6};
    Vector R = vector_init_by_array(3, r);
    vector_scale(R, 0.5);
    cr_assert(vector_get(R, 0) == 1);
    cr_assert(vector_get(R, 1) == 2);
    cr_assert(vector_get(R, 2) == 3);
}

Test(testvector, testadd) {
    int r1[] = {2, 4, 6};
    Vector R1 = vector_init_by_array(3, r1);

    int r2[] = {0, 14, 9};
    Vector R2 = vector_init_by_array(3, r2);

    Vector R = vector_add(R1, R2);
    cr_assert(vector_get(R, 0) == 2, "%d != 2", vector_get(R, 0));
    cr_assert(vector_get(R, 1) == 18, "%d != 28", vector_get(R, 1));
    cr_assert(vector_get(R, 2) == 15, "%d != 15", vector_get(R, 2));       
}
