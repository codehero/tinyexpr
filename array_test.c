#include <stdio.h>
#include <math.h>
#include "tinyexpr.h"

static int test_arrays(void) {
    /* Define two example arrays:
     *  - arr1: length=3, elements {10,20,30}
     *  - arr2: length=2, elements {100,200}
     */
    double arr1[] = { 4, 10, 20, 30, 2 };
    double arr2[] = { 2, 100, 200 };
    double arr3[] = { 2, 300, 600 };
    double arr4[] = { 4, 10, 20, 30, 40 };
    double arr5[] = { 4, 10, 80, 300, 1000 };

    te_variable vars[] = {
        { "arr1", arr1 },
        { "arr2", arr2 },
        { "arr3", arr3 },
        { "arr4", arr4 },
        { "arr5", arr5 }
    };

		int ret = 0;

    struct {
        const char *expr;
        double      expected;
        int         expect_nan;
    } tests[] = {
        /* Basic length & element access */
        { "arr1[0]",      10,    0 },
        { "arr1[1]",      20,    0 },
        { "arr1[2]",      30,    0 },

        /* Arithmetic with lookups */
        { "arr1[1] + arr1[2]",   50, 0 },
        { "arr1[arr1[3] - 1]",   20, 0 },  /* arr1[2] */

        { "arr2[arr1[0] / 10]", 200, 0 },  /* arr1[1]/10 = 1 → arr2[1] = 100 */

        /* Nested lookups across two arrays */
        { "arr2[arr1[1] / 10]", NAN, 1 },  /* arr1[1]/10 = 1 → arr2[1] = 100 */

        /* Out‐of‐bounds */
        { "arr1[  5 ]", NAN, 1 },
        { "arr1[ -1 ]", NAN, 1 },

        /* Non‐integer index (should truncate) */
        { "arr1[1.9]", 20, 0 },  /* casts to idx=1 */
        { "sum(arr1)", 62, 0 },  /* casts to idx=1 */
        { "sum(arr2)", 300, 0 },  /* casts to idx=1 */
        { "linear_interpolate(arr2, arr3, 150)", 450, 0 },  /* casts to idx=1 */
        { "linear_interpolate(arr2, arr3, 50)", NAN, 1 },  /* casts to idx=1 */
        { "linear_interpolate(arr2, arr3, 800)", NAN, 1 },  /* casts to idx=1 */
        { "linear_interpolate(arr4, arr5, 15)", 45, 0 },  /* casts to idx=1 */
        { "linear_interpolate(arr4, arr5, 25)", 190, 0 },  /* casts to idx=1 */
        { "linear_interpolate(arr4, arr5, 35)", 650, 0 },  /* casts to idx=1 */
        { "arrlen(arr4)",4, 0 },  /* casts to idx=1 */
        { "arrlen(arr2)",2, 0 },  /* casts to idx=1 */
        { "arrmax(arr4)",40, 0 },  /* casts to idx=1 */
        { "arrmin(arr4)",10, 0 },  /* casts to idx=1 */
    };

    const int ntests = sizeof(tests) / sizeof(*tests);
    int err;
    for (int i = 0; i < ntests; i++) {
				te_expr *n = te_compile(tests[i].expr, vars, 5, &err);
        double result = te_eval(n);
				te_free(n);
        if (err != 0) {
            printf("FAIL: \"%s\" → parse error (err=%d)\n",
                tests[i].expr, err);
						++ret;
        } else if (tests[i].expect_nan) {
            if (!isnan(result)) {
                printf("FAIL: \"%s\" → got %g but expected NaN\n",
                    tests[i].expr, result);
						++ret;
            } else {
                printf(" PASS: \"%s\" → NaN\n", tests[i].expr);
            }
        } else {
						if(isnan(result)){
				            printf("FAIL: \"%s\" → got NaN but expected %g\n",
                   tests[i].expr, tests[i].expected);
						++ret;
						}
						else if (fabs(result - tests[i].expected) > 1e-9) {
                printf("FAIL: \"%s\" → got %g but expected %g\n",
                    tests[i].expr, result, tests[i].expected);
						++ret;
            } else {
                printf(" PASS: \"%s\" = %g\n",
                    tests[i].expr, result);
            }
        }
    }
		return 0;
}

int main(void) {
    return test_arrays();
}

