//
// Created by jawadhsr on 2/27/17.
//
#include <util.h>
#include "matvec_auto.h"

void matvec_unrolled_auto(int n, float *vec_c, const float *mat_a, const float *vec_b) {
#pragma GCC ivdep
    for (int i = 0; i < n; i++) {
#pragma GCC ivdep
        for (int j = 0; j < n; j += 4) {
            vec_c[i] += mat_a[(i * n) + j] * vec_b[j]
                        + mat_a[(i * n) + j + 1] * vec_b[j + 1]
                        + mat_a[(i * n) + j + 2] * vec_b[j + 2]
                        + mat_a[(i * n) + j + 3] * vec_b[j + 3];
        }
    }
}