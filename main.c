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
            printf("Running simple version\n");
            driveMatVecSSE(mat0, in_vec, out_vec, n);
            printf("Output Vector\n");
            printVector(out_vec, n);
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