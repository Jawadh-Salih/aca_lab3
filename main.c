/**
    Simple test programmes to test SSE instructions
 */

#include <stdio.h>
#include <stdlib.h>
#include<pmmintrin.h>
#include <getopt.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include "util.h"
#include "matvec_drivers.h"
#include "matmat_drivers.h"


int main(int argc, char *argv[]) {
    printf("Starting calculation...\n");
    int c, n = 4;
    const float **mat0 = NULL, **mat1 = NULL, *in_vec = NULL;
    float **mat_ans_c = NULL, **mat_ans_sse = NULL;
    float *out_vec_simple = NULL, *out_vec_sse = NULL, *out_vec_auto = NULL;

    time_t t;
    srand((unsigned) time(&t));

    short mat_vec_ver = 0, mat_mat_ver = 0, c_ver = 0, sse_ver = 0, a_vec_ver = 0, test = 0;

    while ((c = getopt(argc, argv, "n:hvmcsat")) != -1) {
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
            case 't':
                test = 1;
                break;
            case 'h':
                printf("-m\t\t\t-\trun the matrix X matrix version.\n");
                printf("-v\t\t\t-\trun the matrix X vector version.\n");
                printf("-c\t\t\t-\trun the simple version.\n");
                printf("-s\t\t\t-\trun the sse version.\n");
                printf("-a\t\t\t-\trun the auto vectorized version.\n");
                printf("-t\t\t\t-\trun all versions and verify against simple version.\n");
                printf("-h\t\t\t-\tShow this menu\n");
                printf("example for the assignment.\n");
                printf("eg : ./aca_lab3 -n 100 -vc\n");
                printf("\t Run with matrix size 100x100(n), vector size 100(n), simple version(c) - matrix-vector (v)\n");
                printf("eg : ./aca_lab3 -n 10 -vs\n");
                printf("\t Run with matrix size 10x10(n), vector size 10(n), sse version(s) - matrix-vector (v)\n");
                printf("eg : ./aca_lab3 -n 100 -vt\n");
                printf("\t Run with matrix size 100x100(n), vector size 100(n), verification phase(t) - matrix-vector (v)\n");
                printf("eg : ./aca_lab3 -n 100 -mc\n");
                printf("\t Run with two matrices of size 100x100(n) simple version(c) - matrix-matrix (m)\n");
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
        //TODO : Remove from release
//        printf("Input Matrix\n");
//        printNByNMat(mat0, n);
//        printf("Input Vector\n");
//        printVector(in_vec, n);
        // run 10 times get the average time
        if (c_ver || test) {
            out_vec_simple = (float *) malloc(sizeof(float) * n);
            printf("\nRunning simple version\n");
            driveMatVecCPU(mat0, in_vec, out_vec_simple, n);
            //TODO : Remove from release
//            printf("Output Vector\n");
//            printVector(out_vec_simple, n);
        }
        if (sse_ver || test) {
            out_vec_sse = (float *) malloc(sizeof(float) * n);
            printf("\nRunning sse version\n");
            driveMatVecSSE(mat0, in_vec, out_vec_sse, n);
            //TODO : Remove from release
//            printf("Output Vector\n");
//            printVector(out_vec_sse, n);
        }
        if (a_vec_ver || test) {
            out_vec_auto = (float *) malloc(sizeof(float) * n);
            printf("\nRunning auto vectorized version\n");

        }
        free((float *) in_vec);

        if (test) {
            printf("\nVerifying matrix vector multiplication\n");
            printf("Verifying sse and simple...\n");
            float error_sse_simple = 0;
            for (int i = 0; i < n; ++i) {
                error_sse_simple += fabs(out_vec_simple[i] - out_vec_sse[i]);
            }

            if (error_sse_simple > 0.01) {
                printf("\tSSE version verified against simple version - NOT OK\n");
            } else {
                printf("\tSSE version verified against simple version - OK\n");
            }
            printf("Verifying auto and simple...\n");
            float error_auto_simple = 0;
            for (int i = 0; i < n; ++i) {
                error_auto_simple += fabs(out_vec_auto[i] - out_vec_sse[i]);
            }
            if (error_auto_simple > FLT_EPSILON) {
                printf("\tAuto vectorized version verified against simple version - NOT OK\n");
            } else {
                printf("\tAuto vectorized version verified against simple version - OK\n");
            }
        }
        if (out_vec_simple != NULL) {
            free((float *) out_vec_simple);
            out_vec_simple = NULL;
        }
        if (out_vec_sse != NULL) {
            free((float *) out_vec_sse);
            out_vec_sse = NULL;
        }
        if (out_vec_auto != NULL) {
            free((float *) out_vec_auto);
            out_vec_auto = NULL;
        }
    } else if (mat_mat_ver) {
        printf("Program will create two %d x %d matrices for calculations\n", n, n);
        mat1 = matrixCreationNByN(n);
        mat_ans_c = matrixCreationNByN(n);
        mat_ans_sse = matrixCreationNByN(n);
        if (c_ver || test) {
            printf("\nRunning simple version\n");
            driveMatMatCPU(mat0, mat1, mat_ans_c, n);
        }

        if (sse_ver || test) {
            out_vec_sse = (float *) malloc(sizeof(float) * n);
            printf("\nRunning sse version\n");
            driveMatMat_SSE(mat0, mat1, mat_ans_sse, n);
        }

        if (test) {
            printf("\nVerifying matrix matrix multiplication\n");
            printf("Verifying sse and simple...\n");
            float error_sse_simple = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    error_sse_simple += fabs(mat_ans_c[i][j] - mat_ans_sse[i][j]);
                }
            }

            if (error_sse_simple > 0.01) {
                printf("\tSSE version verified against simple version - NOT OK\n");
            } else {
                printf("\tSSE version verified against simple version - OK\n");
            }
        }
        freeNByNMat((float **) mat1, n);
        mat1 = NULL;
    }

    freeNByNMat((float **) mat0, n);
    mat0 = NULL;
    return 0;
}