//
// Created by krv on 3/10/17.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "matmat_drivers.h"
#include "matmat.h"
#include "util.h"
#include "sse_methods.h"

#define GET_TIME(x); if(clock_gettime(CLOCK_MONOTONIC, &(x)) < 0) \
{perror("clock_gettime(): "); exit(EXIT_FAILURE);}

void clearNbyNMatrix(int n, float **mat) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = 0;
        }
    }
}

void driveMatMatCPU(const float **mat_a, const float **mat_b, float **mat_c, int n) {
    struct timespec t0, t1;
    unsigned long sec, nsec;
    float mean, sd;
    time_t t;
    float times[10] = {};
    int req_n = 10;
    for (int i = 0; i < 10; ++i) { GET_TIME(t0);
        matmat_listing7(n, mat_c, mat_a, mat_b);GET_TIME(t1);
        float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
        times[i] = el_t;
        clearNbyNMatrix(n, mat_c);
    }
    mean = Average(times, 10);
    sd = standardDeviation(times, 10);
    req_n = requiredSampleSize(sd, mean);
    printf("Average time : %f\n", mean);
    printf("Required sample size for 95 percent confidence : %d\n", req_n);
    if (req_n > 10) {
        float *times_2 = (float *) malloc(sizeof(float) * req_n);
        printf("Automatically running with required sample size");
        for (int i = 0; i < req_n; ++i) { GET_TIME(t0);
            matmat_listing7(n, mat_c, mat_a, mat_b);GET_TIME(t1);
            float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
            times_2[i] = el_t;
            clearNbyNMatrix(n, mat_c);
        }
        mean = Average(times_2, req_n);
        sd = standardDeviation(times_2, req_n);
        req_n = requiredSampleSize(sd, mean);
        printf("Average time : %f\n", mean);
        free(times_2);
    }
}

void driveMatMat_SSE(const float **mat_a, const float **mat_b, float **mat_c, int n) {
    struct timespec t0, t1;
    unsigned long sec, nsec;
    float mean, sd;
    time_t t;
    float times[10] = {};
    int req_n = 10;
    for (int i = 0; i < 10; ++i) { GET_TIME(t0);
        matmat_listing7_sse(n, mat_c, mat_a, mat_b);GET_TIME(t1);
        float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
        times[i] = el_t;
        clearNbyNMatrix(n, mat_c);
    }
    mean = Average(times, 10);
    sd = standardDeviation(times, 10);
    req_n = requiredSampleSize(sd, mean);
    printf("Average time : %f\n", mean);
    printf("Required sample size for 95 percent confidence : %d\n", req_n);
    if (req_n > 10) {
        float *times_2 = (float *) malloc(sizeof(float) * req_n);
        printf("Automatically running with required sample size");
        for (int i = 0; i < req_n; ++i) { GET_TIME(t0);
            matmat_listing7_sse(n, mat_c, mat_a, mat_b);GET_TIME(t1);
            float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
            times_2[i] = el_t;
            clearNbyNMatrix(n, mat_c);
        }
        mean = Average(times_2, req_n);
        sd = standardDeviation(times_2, req_n);
        req_n = requiredSampleSize(sd, mean);
        printf("Average time : %f\n", mean);
        free(times_2);
    }
}