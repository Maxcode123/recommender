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
