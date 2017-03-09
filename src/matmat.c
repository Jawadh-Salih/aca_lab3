//
// Created by jawadhsr on 2/27/17.
//
#include "matmat.h"
/**
 * Listing 7 - Matrix multiplication
 * @param n : dimension of the nxn matrix
 * @param mat_c : output matrix
 * @param mat_a : input matrix A
 * @param mat_a : input matrix B
 */
void matmat_listing7(int n, float **mat_c,
                     const float **mat_a, const float **mat_b) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
        }
    }
}