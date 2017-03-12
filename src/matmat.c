//
// Created by jawadhsr on 2/27/17.
//
#include "matmat.h"
#include "util.h"
/**
 * Listing 7 - Matrix multiplication
 * @param n : dimension of the nxn matrix
 * @param mat_c : output matrix
 * @param mat_a : input matrix A
 * @param mat_a : input matrix B,
 */
void matmat_listing7(float *mat_c, int a_h, int com_n, const float *mat_a, int b_w, const float *mat_b) {
    for (int i = 0; i < a_h; i++) {
        for (int k = 0; k < com_n; k++) {
            for (int j = 0; j < b_w; j++) {
                mat_c[MINDEX(i, j, com_n)] += mat_a[MINDEX(i, k, com_n)] * mat_b[MINDEX(k, j, com_n)];
            }
        }
    }
}