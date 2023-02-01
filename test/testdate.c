#include <criterion/criterion.h>

#include "../src/preprocess/parser/parser.h"

Test(testdate, testleap) {
    cr_assert(date_leap(2020));
    cr_assert(date_leap(2024));
    cr_assert(date_leap(2028));
    cr_assert(date_leap(2032));
}

Test(testdate, datediff) {
    cr_assert(date_diff(date(10, 1, 2000), date(11, 1, 2000)) == 1);
    cr_assert(date_diff(date(28, 2, 2020), date(1, 3, 2020)) == 2);
    cr_assert(date_diff(date(1, 5, 1987), date(6, 9, 1987)) == 31 + 30 + 31 + 5);
    cr_assert(date_diff(date(2, 8, 2091), date(2, 8, 2092)) == 365);
    cr_assert(date_diff(date(1, 1, 2020), date(1, 1, 2021)) == 366);
}
