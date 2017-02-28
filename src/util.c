//
// Created by jawadhsr on 2/27/17.
//

#include "util.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// N = (100zs/rx)^2, r - accuracy (5%), s - standard deviation, x - Average, z = 1.960 (95%) - TAKE THE CEIL
/// This function gives the required number of samples to take to achieve
/// accuracy of 5% and 95% confidence
/// \param sd standard deviation
/// \param mean average
/// \return

long requiredSampleSize(float sd, float mean) {
    long N = (long) ceil(((float) 100 * 1.960 * sd) / (5 * mean));
    return N;
}

float Average(float *times, int numSamples) {
    float sum = 0;
    for (int i = 0; i < numSamples; ++i) {
        sum += times[i];
    }
    return (double) sum / numSamples;
}

float standardDeviation(float times[], int numSamples) {
    float u = Average(times, numSamples);
    float variance = 0;
    for (int i = 0; i < numSamples; ++i) {
        variance += pow(times[i] - u, 2);
    }
    variance = variance / numSamples;
    return sqrt(variance);
}

float elapsed_time_nsec(struct timespec *begin, struct timespec *end,
                        unsigned long *sec, unsigned long *nsec) {
    if (end->tv_nsec < begin->tv_nsec) {
        *nsec = 1000000000 - (begin->tv_nsec - end->tv_nsec);
        *sec = end->tv_sec - begin->tv_sec - 1;
    } else {
        *nsec = end->tv_nsec - begin->tv_nsec;
        *sec = end->tv_sec - begin->tv_sec;
    }
    return (float) (*sec) * 1000000 + ((float) (*nsec));
}


float elapsed_time_microsec(struct timespec *begin, struct timespec *end,
                            unsigned long *sec, unsigned long *nsec) {
    if (end->tv_nsec < begin->tv_nsec) {
        *nsec = 1000000000 - (begin->tv_nsec - end->tv_nsec);
        *sec = end->tv_sec - begin->tv_sec - 1;
    } else {
        *nsec = end->tv_nsec - begin->tv_nsec;
        *sec = end->tv_sec - begin->tv_sec;
    }
    return (float) (*sec) * 1000000 + ((float) (*nsec)) / 1000.0;
}

float elapsed_time_msec(struct timespec *begin, struct timespec *end,
                        unsigned long *sec, unsigned long *nsec) {
    if (end->tv_nsec < begin->tv_nsec) {
        *nsec = 1000000000 - (begin->tv_nsec - end->tv_nsec);
        *sec = end->tv_sec - begin->tv_sec - 1;
    } else {
        *nsec = end->tv_nsec - begin->tv_nsec;
        *sec = end->tv_sec - begin->tv_sec;
    }
    return (float) (*sec) * 1000 + ((float) (*nsec)) / 1000000.0;
}

const float **matrixCreationNByN(int n) {
    float **mat = (float **) malloc(sizeof(float *) * n);
    for (int i = 0; i < n; ++i) {
        mat[i] = (float *) malloc(sizeof(float) * n);
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            mat[j][i] = rand() % 10;
        }
    }
    return (const float **)mat;
}

void freeNByNMat(float **mat, int n) {
    for (int i = 0; i < n; ++i) {
        free(mat[i]);
    }
    free(mat);
}

void printNByNMat(const float **mat, int n) {
    if (mat != NULL) {
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                printf("%3.3f  ", mat[j][i]);
            }
            printf("\n");
        }
    }
}

const float *vectorCreation(int n) {
    float *vec = (float *) malloc(sizeof(float) * n);
    for (int j = 0; j < n; ++j) {
        vec[j] = rand() % 10;
    }
    return vec;
}

void printVector(const float *vec, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%3.3f  ", vec[i]);
    }
    printf("\n");
}