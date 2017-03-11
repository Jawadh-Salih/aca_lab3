//
// Created by jawadhsr on 2/27/17.
//
#include <time.h>

#ifndef ACA_LAB3_UTIL_H
#define ACA_LAB3_UTIL_H

float **matrixCreationNByN_Empty(int r, int c);

const float **matrixCreationNByN(int r, int c);

void freeNMat(float **mat, int n);

void printNByCMat(const float **mat, int n, int c);
const float *vectorCreation(int n);
void printVector(const float *vec, int n);
float elapsed_time_microsec(struct timespec *begin, struct timespec *end,
                            unsigned long *sec, unsigned long *nsec);
float standardDeviation(float times[], int numSamples);
float Average(float *times, int numSamples);
long requiredSampleSize(float sd, float mean);

void cleanVector(float *vec, int n);

void clearNbyNMatrix(int n, int c, float **mat);

#endif //ACA_LAB3_UTIL_H
