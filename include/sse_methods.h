//
// Created by krv on 2/28/17.
//

#ifndef ACA_LAB3_SSE_METHODS_H
#define ACA_LAB3_SSE_METHODS_H

void test(int n, float *vec_c, const float **mat_a, const float *vec_b);

void matvec_unrolled_sse_quite(int n, float *vec_c, const float **mat_a, const float vec_b[n]);

void matmat_listing7_sse(int n, float **mat_c, const float **mat_a, const float **mat_b);

#endif //ACA_LAB3_SSE_METHODS_H
