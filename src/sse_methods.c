//
// Created by krv on 2/28/17.
//
#include <xmmintrin.h>
#include <stdio.h>
#include <pmmintrin.h>
#include "sse_methods.h"

void test(int n, float *vec_c, const float **mat_a, const float *vec_b) {

    __m128 x0 = _mm_loadu_ps(&vec_b[0]);
    printf("Loading vector ok\n");
//    __m128 two_v = _mm_set1_ps(2);
    printf("Storing vector ok\n");
    _mm_storeu_ps(&vec_c[0], x0);


}

void matvec_unrolled_sse_quite(int n, float *vec_c, const float mat_a[n][n], const float vec_b[n]) {

    // NOTE : Matrix and Vector both must have dimensions which are multiples of 4
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 4) {
            // load the vector

            __m128 temp = _mm_loadu_ps(&vec_c[i]);

            __m128 x0 = _mm_loadu_ps(&vec_b[j]);

            // load the matirx mat_a current section to a v0-v1 four vectors
            __m128 v0 = _mm_loadu_ps(&mat_a[i][j]);

            // multiplication
            __m128 m0 = _mm_mul_ps(x0, v0);

            // reduction
            // TODO : We are wasting 3 locations of the rslts vector we can process 4 outputs for
            // output vector and for that we need 16x16 block from input matrix and 16 length from input vector
            // any idea
            __m128 zero_v = _mm_setzero_ps();
            __m128 sm0 = _mm_hadd_ps(m0, zero_v);
            __m128 rslt = _mm_hadd_ps(sm0, zero_v);
            rslt = _mm_add_ps(rslt, temp);
            _mm_storeu_ps(&vec_c[i], rslt);
        }
    }
}