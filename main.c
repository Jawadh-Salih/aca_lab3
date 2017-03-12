/**
    Simple test programmes to test SSE instructions
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <float.h>
#include <unistd.h>
#include "main_drivers.h"
#include "util.h"

//#define DEBUG

#ifdef DEBUG
#define COLUMNS 4
#else
#define COLUMNS 200
#endif


int main(int argc, char *argv[]) {
    printf("Starting calculation...\n");
    int c, n = 4;
    const float **mat0 = NULL, **mat1 = NULL, *in_vec = NULL;
    float **mat_ans_c = NULL, **mat_ans_sse = NULL, **mat_ans_auto = NULL;
    float *out_vec_simple = NULL, *out_vec_sse = NULL, *out_vec_auto = NULL, *out_vec_simple_list6 = NULL;
    int cols = COLUMNS;
    time_t t;
    srand((unsigned) time(&t));

    short mat_vec_ver = 0, mat_mat_ver = 0, c_ver = 0, sse_ver = 0, a_vec_ver = 0, test = 0, listing6;

    while ((c = getopt(argc, argv, "n:hvmcsat5")) != -1) {
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
            case '5':
                listing6 = 1;
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
#ifdef DEBUG
    n = 8;
    t = 1;
    mat_mat_ver = 1;
    mat_vec_ver = 1;
#endif
    mat0 = matrixCreationNByN(n, n);

    if (mat_vec_ver) {
        printf("Program will create %d x %d matrix and a %dx1 vector for calculations\n", n, n, n);
        // vector creation
        in_vec = vectorCreation(n);
#ifdef DEBUG
        printf("Input Matrix\n");
        printNByCMat(mat0, n, n);
        printf("Input Vector\n");
        printVector(in_vec, n);
#endif
        // run 10 times get the average time
        if (c_ver || test) {
            sleep(1);
            out_vec_simple = (float *) malloc(sizeof(float) * n);
            printf("\nRunning listing 5 C Program\n");
            driveMatVecCPU_listing5(mat0, in_vec, out_vec_simple, n);
        }
        if (listing6 || test) {
            sleep(1);
            out_vec_simple_list6 = (float *) malloc(sizeof(float) * n);
            printf("\nRunning listing 6 C Program\n");
            driveMatVecCPU_listing6(mat0, in_vec, out_vec_simple_list6, n);
        }
        if (sse_ver || test) {
            sleep(1);
            out_vec_sse = (float *) malloc(sizeof(float) * n);
            printf("\nRunning sse version\n");
            driveMatVecSSE(mat0, in_vec, out_vec_sse, n);
        }
        if (a_vec_ver || test) {
            sleep(1);
            out_vec_auto = (float *) malloc(sizeof(float) * n);
            printf("\nRunning auto vectorized version\n");
            driveMatVecAuto(mat0, in_vec, out_vec_auto, n);
        }
        free((float *) in_vec);

        if (test) {
            printf("\nVerifying matrix vector multiplication\n");
            printf("Verifying sse (listing 6) and listing 5 C Program.\n");
            float error_sse_simple = 0;
            for (int i = 0; i < n; ++i) {
                error_sse_simple += fabsf(out_vec_simple[i] - out_vec_sse[i]);
            }

            if (error_sse_simple > FLT_EPSILON || isnanf(error_sse_simple)) {
                printf("\tSSE (listing 6) version verified against listing 5 C Program - NOT OK\n");
            } else {
                printf("\tSSE (listing 6) version verified against listing 5 C Program - OK\n");
            }
            printf("Verifying Listing 6 C and listing 5 C Program.\n");
            float error_list6_simple = 0;
            for (int i = 0; i < n; ++i) {
                error_list6_simple += fabsf(out_vec_simple_list6[i] - out_vec_simple[i]);
            }

            if (error_list6_simple > FLT_EPSILON || isnanf(error_list6_simple)) {
                printf("\tListing 6 C Program verified against listing 5 C Program - NOT OK\n");
            } else {
                printf("\tListing 6 C Program verified against listing 5 C Program - OK\n");
            }

            printf("Verifying auto and simple...\n");
            float error_auto_simple = 0;
            for (int i = 0; i < n; ++i) {
                error_auto_simple += fabsf(out_vec_auto[i] - out_vec_simple[i]);
            }
            if (error_auto_simple > FLT_EPSILON || isnanf(error_auto_simple)) {
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
    }
    if (mat_mat_ver) {
        printf("Program will create random one %d x %d matrix and one %d x 200 matrix for calculations\n", n, n, n);
        mat1 = matrixCreationNByN(n, cols);
#ifdef DEBUG
        printf("Matrix A\n");
        printNByCMat(mat0, n, n);
        printf("Matrix B\n");
        printNByCMat(mat1, n, cols);
#endif
        if (c_ver || test) {
            sleep(1);
            mat_ans_c = matrixCreationNByN_Empty(n, cols);
            printf("\nRunning mxm listing 7 C Program\n");
            driveMatMatCPU(mat0, mat1, mat_ans_c, n, cols);
#ifdef DEBUG
            printf("Matrix mat_ans_c\n");
            printNByCMat(mat_ans_c, n, cols);
#endif
        }

        if (sse_ver || test) {
            sleep(1);
            mat_ans_sse = matrixCreationNByN_Empty(n, cols);
            printf("\nRunning mxm listing 7 SSE version\n");
            driveMatMat_SSE(mat0, mat1, mat_ans_sse, n, cols);
#ifdef DEBUG
            printf("Matrix mat_ans_sse\n");
            printNByCMat(mat_ans_sse, n, cols);
#endif
        }

        if (a_vec_ver || test) {
            sleep(1);
            mat_ans_auto = matrixCreationNByN_Empty(n, cols);
            printf("\nRunning mxm listing 7 auto vectorized version\n");
            driveMatMatAuto(mat0, mat1, mat_ans_auto, n, cols);
        }

        if (test) {
            printf("\nVerifying matrix matrix multiplication\n");
            printf("Verifying listing 7 SSE and listing 7 C Program\n");
            float error_sse_simple = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < cols; ++j) {
                    error_sse_simple += fabsf(mat_ans_c[i][j] - mat_ans_sse[i][j]);
                }
            }
            if (error_sse_simple > FLT_EPSILON || isnanf(error_sse_simple)) {
                printf("\tListing 7 SSE mxm version verified against listing 7 C Program - NOT OK\n");
            } else {
                printf("\tListing 7 SSE mxm version verified against listing 7 C Program - OK\n");
            }

            printf("Verifying listing 7 auto vectorized version and listing 7 C Program.\n");
            float error_auto_simple = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < cols; ++j) {
                    error_auto_simple += fabsf(mat_ans_c[i][j] - mat_ans_auto[i][j]);
                }
            }

            if (error_auto_simple > FLT_EPSILON || isnanf(error_auto_simple)) {
                printf("\tListing 7 auto vectorized version verified against listing 7 C Program - NOT OK\n");
            } else {
                printf("\tListing 7 auto vectorized version verified against listing 7 C Program - OK\n");
            }
        }
        freeNMat((float **) mat1, n);
        mat1 = NULL;

        if (mat_ans_auto != NULL) {
            freeNMat(mat_ans_auto, n);
            mat_ans_auto = NULL;
        }
        if (mat_ans_sse != NULL) {
            freeNMat(mat_ans_sse, n);
            mat_ans_sse = NULL;
        }
        if (mat_ans_c != NULL) {
            freeNMat(mat_ans_c, n);
            mat_ans_c = NULL;
        }
    }

    freeNMat((float **) mat0, n);
    mat0 = NULL;
    return 0;
}