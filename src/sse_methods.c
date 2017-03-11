//
// Created by krv on 2/28/17.
//
#include <xmmintrin.h>
#include <pmmintrin.h>
#include "sse_methods.h"

void matvec_unrolled_sse_quite(int n, float *vec_c, const float **mat_a, const float *vec_b) {
    __m128 zero_v = _mm_setzero_ps();
    // NOTE : Matrix and Vector both must have dimensions which are multiples of 4
    for (int i = 0; i < n; i += 1) {
        __m128 temp = _mm_loadu_ps(&vec_c[i]);
        for (int j = 0; j < n; j += 4) {
            // load the vector


            __m128 x0 = _mm_loadu_ps(&vec_b[j]);

            // load the matirx mat_a current section to a v0-v1 four vectors
            __m128 v0 = _mm_loadu_ps(&mat_a[i][j]);

            // multiplication
            __m128 m0 = _mm_mul_ps(x0, v0);

            // reduction
            // TODO : We are wasting 3 locations of the rslts vector we can process 4 outputs for
            // output vector and for that we need 16x16 block from input matrix and 16 length from input vector
            // any idea

            __m128 sm0 = _mm_hadd_ps(m0, zero_v);
            __m128 rslt = _mm_hadd_ps(sm0, zero_v);
            temp = _mm_add_ps(rslt, temp);
        }
        _mm_storeu_ps(&vec_c[i], temp);
    }
}

void matvec_unrolled_16sse(int n, float *vec_c, const float **mat_a, const float *vec_b) {

    // NOTE : Matrix and Vector both must have dimensions which are multiples of 4
    int unroll16Size = n / 16;  // expect an integer division
    int unrolled_num = unroll16Size * 16;
    int rest = n - unrolled_num;
    // 0,0,0,0 = zero_v
    __m128 zero_v = _mm_setzero_ps();

    for (int i = 0; i < n; i += 1) {
        int j = 0;
        __m128 row_result = _mm_loadu_ps(&vec_c[i]);
        for (int k = 0; k < unroll16Size; ++k) {
            for (; j < unrolled_num; j += 16) {

                // load next 4 floats from input vector
                __m128 x0 = _mm_loadu_ps(&vec_b[j]);
                // load next 4 floats from input vector
                __m128 x1 = _mm_loadu_ps(&vec_b[j + 4]);
                // load next 4 floats from input matrix
                __m128 v0 = _mm_loadu_ps(&mat_a[i][j]);
                // load next 4 floats from input matrix
                __m128 v1 = _mm_loadu_ps(&mat_a[i][j + 4]);

                // multiply first 4 elements of input vector and input matrix
                __m128 m0 = _mm_mul_ps(x0, v0);
                // multiply next 4 elements of input vector and input matrix
                __m128 m1 = _mm_mul_ps(x1, v1);

                // load next 4 floats from input vector
                x0 = _mm_loadu_ps(&vec_b[j + 8]);
                // load next 4 floats from input vector
                x1 = _mm_loadu_ps(&vec_b[j + 12]);
                // load next 4 floats from input matrix
                v0 = _mm_loadu_ps(&mat_a[i][j + 8]);
                // load next 4 floats from input matrix
                v1 = _mm_loadu_ps(&mat_a[i][j + 12]);

                __m128 m2 = _mm_mul_ps(x0, v0);
                __m128 m3 = _mm_mul_ps(x1, v1);

                // reduction
                // m00,m01,m02,m03 + m10,m11,m12,m13  = m00+m01, m02+m03, m10+m11, m12+m13 = sm01
                __m128 sm01 = _mm_hadd_ps(m0, m1);
                // m20,m21,m22,m23 + m30,m31,m32,m33  = m20+m21, m22+m23, m30+m31, m32+m33 = sm23
                __m128 sm23 = _mm_hadd_ps(m2, m3);
                // m00+m01, m02+m03, m10+m11, m12+m13 +  m20+m21, m22+m23, m30+m31, m32+m33 =
                // m00+m01+m02+m03, m10+m11+m12+m13, m20+m21+m22+m23, m30+m31+m32+m33 =
                // sun(m0), sum(m1), sum(m2), sum(m3) = sm_rslt
                __m128 sm_rslt = _mm_hadd_ps(sm01, sm23);

                // sun(m0),sum(m1),sum(m2),sum(m3) + 0,0,0,0 =  sun(m0)+sum(m1), sum(m2)+sum(m3) = sm_rs
                __m128 sm_rs = _mm_hadd_ps(sm_rslt, zero_v);
                // sun(m0)+sum(m1),sum(m2)+sum(m3) + 0,0,0,0 = sun(m0)+sum(m1)+sum(m2)+sum(m3) = rslt
                __m128 rslt = _mm_hadd_ps(sm_rs, zero_v);

                row_result = _mm_add_ps(rslt, row_result);

            }
        }
        if (rest > 0) {
            for (j = unrolled_num; j < n; j += 4) {

                __m128 x0 = _mm_loadu_ps(&vec_b[j]);
                __m128 v0 = _mm_loadu_ps(&mat_a[i][j]);

                // multiplication
                __m128 m0 = _mm_mul_ps(x0, v0);

                __m128 sm0 = _mm_hadd_ps(m0, zero_v);
                __m128 rslt = _mm_hadd_ps(sm0, zero_v);
                row_result = _mm_add_ps(rslt, row_result);
            }
        }
        _mm_storeu_ps(&vec_c[i], row_result);
    }
//    printVector(vec_c, n);
}

void matmat_listing7_sse(int n, int c, float **mat_c, const float **mat_a, const float **mat_b) {

    int transposed[c][n];

    for (int l = 0; l < c; ++l) {
        for (int i = 0; i < n; ++i) {
//            transposed[l][i] = mat_b[i][l];
//            __m128 v0 = _mm_loadu_ps(&mat_a[i][k]);
        }
    }

    __m128 zero_v = _mm_setzero_ps();
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < c; j += 1) {
            __m128 temp = _mm_loadu_ps(&mat_c[i][j]);
            for (int k = 0; k < n; k = k + 4) {
                __m128 v0 = _mm_loadu_ps(&mat_a[i][k]);
                __m128 x0 = _mm_loadu_ps(&transposed[j][k]);

                __m128 m0 = _mm_mul_ps(x0, v0);

                __m128 sm0 = _mm_hadd_ps(m0, zero_v);
                __m128 rslt = _mm_hadd_ps(sm0, zero_v);

                temp = _mm_add_ps(rslt, temp);

            }
            _mm_storeu_ps(&mat_c[i][j], temp);
        }
    }
}