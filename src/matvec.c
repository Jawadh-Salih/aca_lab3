//
// Created by jawadhsr on 2/27/17.
//
#include "matvec.h"
#include <stdio.h>
#include <xmmintrin.h>
#include <printf.h>
#include <pmmintrin.h>
void  matvec_simple ( int n , float * vec_c ,
                const float ** mat_a , const float * vec_b)
{
    for ( int i = 0; i < n ; i ++)
        for ( int j = 0; j < n ; j ++)
            vec_c [ i ] += mat_a [ i ] [ j ] * vec_b [ j ] ;
}

void matvec_unrolled(int n,float *vec_c, const float** mat_a, const float *vec_b){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j+=4){
            vec_c[i] += mat_a[i][j]*vec_b[j]
                        + mat_a[i][j+1]*vec_b[j+1]
                        + mat_a[i][j+2]*vec_b[j+2]
                        + mat_a[i][j+3]*vec_b[j+3];
        }
    }
}

void matvec_unrolled_sse(int n, float *vec_c, const float mat_a[n][n], const float vec_b[n]) {

    // NOTE : Matrix and Vector both must have dimensions which are multiples of 4
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 4) {
            // load the vector

            __m128 temp = _mm_loadu_ps(&vec_c[i]);

            __m128 x0 = _mm_loadu_ps(&vec_b[j]);
            printf("Loading vector ok\n");

            // load the matirx mat_a current section to a v0-v1 four vectors
            __m128 v0 = _mm_loadu_ps(&mat_a[i][j]);
            printf("Loading matrix ok\n");

            // multiplication
            __m128 m0 = _mm_mul_ps(x0, v0);
            printf("Multiplication ok\n");

            // reduction
            // TODO : We are wasting 3 locations of the rslts vector we can process 4 outputs for
            // output vector and for that we need 16x16 block from input matrix and 16 length from input vector
            // any idea
            __m128 zero_v = _mm_setzero_ps();
            __m128 sm0 = _mm_hadd_ps(m0, zero_v);
            __m128 rslt = _mm_hadd_ps(sm0, zero_v);
            rslt = _mm_add_ps(rslt, temp);

            printf("Horizontal addition ok\n");

            _mm_storeu_ps(&vec_c[i], rslt);
        }
    }
}
