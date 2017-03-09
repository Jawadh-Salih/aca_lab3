//
// Created by krv on 2/28/17.
//

#include "matvec_drivers.h"
#include "matvec.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sse_methods.h>
#include "util.h"

#define GET_TIME(x); if(clock_gettime(CLOCK_MONOTONIC, &(x)) < 0) \
{perror("clock_gettime(): "); exit(EXIT_FAILURE);}

void cleanVector(float *vec, int n);

void driveMatVecCPU(const float ** mat, const float * vec_in, float * vec_out, int n){
    struct timespec t0, t1;
    unsigned long sec, nsec;
    float mean, sd;
    time_t t;
    float times[10] = {};
    int req_n = 10;
    for (int i = 0; i < 10; ++i) {
        cleanVector(vec_out, n);
        GET_TIME(t0);
        matvec_simple(n, vec_out, mat, vec_in);
        GET_TIME(t1);
        float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
        times[i] = el_t;
    }
    mean = Average(times, 10);
    sd = standardDeviation(times, 10);
    req_n = requiredSampleSize(sd, mean);
    printf("Average time : %f\n", mean);
    printf("Required sample size for 95 percent confidence : %d\n", req_n);
    if (req_n > 10) {
        float *times_2 = (float *) malloc(sizeof(float) * req_n);
        printf("Automatically running with required sample size");
        for (int i = 0; i < req_n; ++i) {
            cleanVector(vec_out, n);GET_TIME(t0);
            matvec_simple(n, vec_out, mat, vec_in);GET_TIME(t1);
            float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
            times_2[i] = el_t;
        }
        mean = Average(times_2, req_n);
        sd = standardDeviation(times_2, req_n);
        req_n = requiredSampleSize(sd, mean);
        printf("Average time : %f\n", mean);
        free(times_2);
    }
}


void driveMatVecSSE(const float **mat, const float *vec_in, float *vec_out, int n) {
    struct timespec t0, t1;
    unsigned long sec, nsec;
    float mean, sd;
    time_t t;
    float times[10] = {};
    int req_n;
    for (int i = 0; i < 10; ++i) {
        cleanVector(vec_out, n);GET_TIME(t0);
        matvec_unrolled_sse_quite(n, vec_out, mat, vec_in);GET_TIME(t1);
        float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
        times[i] = el_t;
    }
    mean = Average(times, 10);
    sd = standardDeviation(times, 10);
    req_n = requiredSampleSize(sd, mean);
    printf("Average time : %f\n", mean);
    printf("Required sample size for 95 percent confidence : %d\n", req_n);
    if(req_n > 10){
        float *times_2 = (float *) malloc(sizeof(float) * req_n);
        printf("Automatically running with required sample size");
        for (int i = 0; i < req_n; ++i) {
            cleanVector(vec_out, n);GET_TIME(t0);
            matvec_unrolled_sse_quite(n, vec_out, mat, vec_in);GET_TIME(t1);GET_TIME(t1);
            float el_t = elapsed_time_microsec(&t0, &t1, &sec, &nsec);
            times_2[i] = el_t;
        }
        mean = Average(times_2, req_n);
        sd = standardDeviation(times_2, req_n);
        req_n = requiredSampleSize(sd,mean);
        printf("Average time : %f\n", mean);
        free(times_2);
    }
}

void cleanVector(float *vec, int n) {
    for (int i = 0; i < n; ++i) {
        vec[i] = 0;
    }
}