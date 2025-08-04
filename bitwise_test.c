#include <stdio.h>
#include <math.h>
#include "tinyexpr.h"

int main() {
    int err;
    int pass = 0, fail = 0;
    te_variable vars[] = {
    };

    err = 0;
    te_expr *e0 = te_compile("5 & 3", vars, 0, &err);
    if (e0) {
        double result = te_eval(e0);
        if ((fabs(result - 1.0) < 1e-9)) {
            printf("PASS: 5 & 3 = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: 5 & 3 = %.1f (expected 1.0)\n", result);
            fail++;
        }
        te_free(e0);
    } else {
        printf("FAIL: compile error for 5 & 3 (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e1 = te_compile("5 | 2", vars, 0, &err);
    if (e1) {
        double result = te_eval(e1);
        if ((fabs(result - 7.0) < 1e-9)) {
            printf("PASS: 5 | 2 = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: 5 | 2 = %.1f (expected 7.0)\n", result);
            fail++;
        }
        te_free(e1);
    } else {
        printf("FAIL: compile error for 5 | 2 (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e2 = te_compile("bit(5, 0)", vars, 0, &err);
    if (e2) {
        double result = te_eval(e2);
        if ((fabs(result - 1.0) < 1e-9)) {
            printf("PASS: bit(5, 0) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: bit(5, 0) = %.1f (expected 1.0)\n", result);
            fail++;
        }
        te_free(e2);
    } else {
        printf("FAIL: compile error for bit(5, 0) (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e3 = te_compile("bit(5, 1)", vars, 0, &err);
    if (e3) {
        double result = te_eval(e3);
        if ((fabs(result - 0.0) < 1e-9)) {
            printf("PASS: bit(5, 1) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: bit(5, 1) = %.1f (expected 0.0)\n", result);
            fail++;
        }
        te_free(e3);
    } else {
        printf("FAIL: compile error for bit(5, 1) (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e4 = te_compile("bit(5, 2)", vars, 0, &err);
    if (e4) {
        double result = te_eval(e4);
        if ((fabs(result - 1.0) < 1e-9)) {
            printf("PASS: bit(5, 2) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: bit(5, 2) = %.1f (expected 1.0)\n", result);
            fail++;
        }
        te_free(e4);
    } else {
        printf("FAIL: compile error for bit(5, 2) (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e5 = te_compile("xor(5, 3)", vars, 0, &err);
    if (e5) {
        double result = te_eval(e5);
        if ((fabs(result - 6.0) < 1e-9)) {
            printf("PASS: xor(5, 3) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: xor(5, 3) = %.1f (expected 6.0)\n", result);
            fail++;
        }
        te_free(e5);
    } else {
        printf("FAIL: compile error for xor(5, 3) (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e6 = te_compile("bit(1024, 10)", vars, 0, &err);
    if (e6) {
        double result = te_eval(e6);
        if ((fabs(result - 1.0) < 1e-9)) {
            printf("PASS: bit(1024, 10) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: bit(1024, 10) = %.1f (expected 1.0)\n", result);
            fail++;
        }
        te_free(e6);
    } else {
        printf("FAIL: compile error for bit(1024, 10) (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e7 = te_compile("bit(1024, 9)", vars, 0, &err);
    if (e7) {
        double result = te_eval(e7);
        if ((fabs(result - 0.0) < 1e-9)) {
            printf("PASS: bit(1024, 9) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: bit(1024, 9) = %.1f (expected 0.0)\n", result);
            fail++;
        }
        te_free(e7);
    } else {
        printf("FAIL: compile error for bit(1024, 9) (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e8 = te_compile("xor(255, 170)", vars, 0, &err);
    if (e8) {
        double result = te_eval(e8);
        if ((fabs(result - 85.0) < 1e-9)) {
            printf("PASS: xor(255, 170) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: xor(255, 170) = %.1f (expected 85.0)\n", result);
            fail++;
        }
        te_free(e8);
    } else {
        printf("FAIL: compile error for xor(255, 170) (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e9 = te_compile("5 & -1", vars, 0, &err);
    if (e9) {
        double result = te_eval(e9);
        if (isnan(result)) {
            printf("PASS: 5 & -1 = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: 5 & -1 = %.1f (expected NaN)\n", result);
            fail++;
        }
        te_free(e9);
    } else {
        printf("FAIL: compile error for 5 & -1 (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e10 = te_compile("2^10", vars, 0, &err);
    if (e10) {
        double result = te_eval(e10);
        if ((fabs(result - 1024.0) < 1e-9)) {
            printf("PASS: 2^10 = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: 2^10 = %.1f (expected 1024.0)\n", result);
            fail++;
        }
        te_free(e10);
    } else {
        printf("FAIL: compile error for 2^10 (err pos = %d)\n", err);
        fail++;
    }

    err = 0;
    te_expr *e11 = te_compile("5 | (1 << 53)", vars, 0, &err);
    if (e11) {
        double result = te_eval(e11);
        if (isnan(result)) {
            printf("PASS: 5 | (1 << 53) = %.1f\n", result);
            pass++;
        } else {
            printf("FAIL: 5 | (1 << 53) = %.1f (expected NaN)\n", result);
            fail++;
        }
        te_free(e11);
    } else {
        printf("FAIL: compile error for 5 | (1 << 53) (err pos = %d)\n", err);
        fail++;
    }

    printf("\nSummary: %d passed, %d failed\n", pass, fail);
    return fail;
}
