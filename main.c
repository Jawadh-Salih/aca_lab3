/**
    Simple test programmes to test SSE instructions
 */

#include <stdio.h>
#include <stdlib.h>
#include<pmmintrin.h>
#include <getopt.h>
#include <time.h>
#include "util.h"
#include "matvec_drivers.h"


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

    // NOTE : Matrix and Vector both must have dimensions which are multiples of 4
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < n; j += 4) {
            // load the vector
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
            printf("Horizontal addition ok\n");

            _mm_storeu_ps(&vec_c[i], rslt);
        }
    }
}

static void test(int n, float *vec_c, const float **mat_a, const float *vec_b) {

    __m128 x0 = _mm_loadu_ps(&vec_b[0]);
    printf("Loading vector ok\n");
//    __m128 two_v = _mm_set1_ps(2);
    printf("Storing vector ok\n");
    _mm_storeu_ps(&vec_c[0], x0);


}

int main(int argc, char *argv[]) {
    printf("Starting calculation...\n");
    int c, n = 4;
    const float ** mat0, **mat1, *in_vec;
    float *out_vec;


    short mat_vec_ver = 0, mat_mat_ver = 0, c_ver = 0, sse_ver = 0, a_vec_ver = 0;

    while ((c = getopt(argc, argv, "n:hvmcsa")) != -1) {
        switch (c) {
            case 'n':
                n = atoi(optarg);
                break;
            case 'v':
                mat_vec_ver = 1;
                break;
            case 'c':
                c_ver = 1;
                break;
            case 's':
                sse_ver = 1;
                break;
            case 'a':
                a_vec_ver = 1;
                break;
            case 'm':
                mat_mat_ver = 1;
                break;
            case 'h':
                printf("-m\t\t\t-\trun the matrix X matrix version.\n");
                printf("-v\t\t\t-\trun the matrix X vector version.\n");
                printf("-c\t\t\t-\trun the cpu version.\n");
                printf("-s\t\t\t-\trun the sse version.\n");
                printf("-a\t\t\t-\trun the auto vectorized version.\n");
                printf("-h\t\t\t-\tShow this menu\n");
                printf("example for the assignment.\n");
                printf("eg : ./aca_lab3 -n 100 -v\n");
                printf("eg : ./aca_lab3 -n 100 -m\n");
                printf("eg : ./aca_lab3 -h\n");
                break;
            case '?':
                if (optopt == 'n') {
                    fprintf(stderr, "Option -n requires an integer point argument\n");
                } else {
                    fprintf(stderr, "Unknown option character\n");
                }
                return 1;
            default:
                abort();
        }
    }
    // matrix creation
    mat0 = matrixCreationNByN(n);

    if (mat_vec_ver) {
        printf("Program will create %d x %d matrix and a %dx1 vector for calculations\n", n, n, n);
        // vector creation
        in_vec = vectorCreation(n);
        printf("Input Matrix\n");
        printNByNMat(mat0, n);
        printf("Input Vector\n");
        printVector(in_vec, n);
        // run 10 times get the average time
        out_vec = (float *) malloc(sizeof(float)*n);
        if(c_ver) {
            printf("Running simple version\n");
            driveMatVecCPU(mat0, in_vec, out_vec, n);
            printf("Output Vector\n");
            printVector(out_vec, n);
        }
        if(sse_ver){
            printf("Running sse version\n");
        }
        if(a_vec_ver) {
            printf("Running auto vectorized version\n");

        }
        free((float *)in_vec);
        free((float *)out_vec);
    } else if (mat_mat_ver) {
        printf("Program will create two %d x %d matrices for calculations\n", n, n);
        mat1 = matrixCreationNByN(n);
        freeNByNMat((float **)mat1,n);
    }

    freeNByNMat((float **)mat0, n);
    return 0;
}