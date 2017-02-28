/**
    Simple test programmes to test SSE instructions
 */

#include <stdio.h>
//#include <stdlib.h>
#include<pmmintrin.h>
//#include<smmintrin.h>
//#include<tmmintrin.h>
//#include<xmmintrin.h>
//#include <xmmintrin.h>	// Need this for SSE compiler intrinsics
//#include <math.h>		// Needed for sqrt in CPU-only version

static void matvec_unrolled(int n, float vec_c[n], const float mat_a[n][n], const float vec_b[n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j += 4) {
            vec_c[i] += mat_a[i][j] * vec_b[j]
                        + mat_a[i][j + 1] * vec_b[j + 1]
                        + mat_a[i][j + 2] * vec_b[j + 2]
                        + mat_a[i][j + 3] * vec_b[j + 3];
        }
    }
}

static void matvec_unrolled_sse(int n, float *vec_c, const float mat_a[n][n], const float vec_b[n]) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j += 4) {
            // load the vector
            __m128 x0 = _mm_loadu_ps(&vec_b[j]);
//            __m128 oldRes = _mm_loadu_ps(&vec_c[i]);
            printf("Loading vector ok\n");

            // load the matirx mat_a current section to a v0-v1 four vectors
            __m128 v0 = _mm_loadu_ps(&mat_a[i][j]);
            printf("Loading matrix ok\n");

//            // multiplication
            __m128 m0 = _mm_mul_ps(x0, v0);
            printf("Multiplication ok\n");

//            // reduction
//            __m128 sm0 = _mm_hadd_ps(m0,m1);
//            __m128 sm1 = _mm_hadd_ps(m2,m3);
//            __m128 rslt = _mm_hadd_ps(sm0,sm1);
//            printf("Horizontal addition ok\n");

//            __m128 newSum = _mm_add_ps(oldRes,v0);
            _mm_storeu_ps(&vec_c[i], m0);
        }
    }
}

static void test(int n, float *vec_c, const float ** mat_a, const float * vec_b) {

    __m128 x0 = _mm_loadu_ps(&vec_b[0]);
    printf("Loading vector ok\n");
//    __m128 two_v = _mm_set1_ps(2);
    printf("Storing vector ok\n");
    _mm_storeu_ps(&vec_c[0], x0);


}

int main(int argc, char *argv[]) {
    printf("Starting calculation...\n");
    int n = 4;
    float mat[4][4] = {{1, 2, 3, 4},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}};
    float vec[4] = {1, 1, 1, 1};
    float vec_seq[4]={0};
    float vec_sse[4]={0};

    matvec_unrolled(n, vec_seq, mat, vec);
    for (int i = 0; i < n; ++i) {
        printf("%f ", vec_seq[i]);
    }
    printf("\nLoop unrolled simple -- OK\n");

    test(n, vec_sse, mat, vec);
    printf("\nLoop unrolled SSE3  -- OK\n");
    for (int i = 0; i < n; ++i) {
        printf("%f ", vec_sse[i]);
    }


    printf("\nLoop unrolled SSE3  -- OK\n");
    printf("Programme ran...\n");
    return 0;
}