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


int main(int argc, char *argv[]) {
    printf("Starting calculation...\n");
    int c, n = 4;
    const float **mat0, **mat1, *in_vec;
    float *out_vec_simple;
    float *out_vec_sse;
    float *out_vec_auto;
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
//        printf("Input Matrix\n");
//        printNByNMat(mat0, n);
//        printf("Input Vector\n");
//        printVector(in_vec, n);
        // run 10 times get the average time
        if (c_ver || test) {
            out_vec_simple = (float *) malloc(sizeof(float) * n);
            printf("\nRunning simple version\n");
            driveMatVecCPU(mat0, in_vec, out_vec_simple, n);
            printf("Output Vector\n");
//            printVector(out_vec_simple, n);
        }
        if (sse_ver || test) {
            out_vec_sse = (float *) malloc(sizeof(float) * n);
            printf("\nRunning sse version\n");
            printf("Running simple version\n");
            driveMatVecSSE(mat0, in_vec, out_vec_sse, n);
            printf("Output Vector\n");
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
        free((float *) out_vec_simple);
        free((float *) out_vec_sse);
        free((float *) out_vec_auto);
    } else if (mat_mat_ver) {
        printf("Program will create two %d x %d matrices for calculations\n", n, n);
        mat1 = matrixCreationNByN(n);
        freeNByNMat((float **) mat1, n);
    }

    freeNByNMat((float **) mat0, n);
    return 0;
}