//
// Created by jawadhsr on 2/27/17.
//

#ifndef ACA_LAB3_UTIL_H
#define ACA_LAB3_UTIL_H

#include <time.h>

const float ** matrixCreationNByN(int n);
void freeNByNMat(float ** mat, int n);
void printNByNMat(const float ** mat, int n);
const float *vectorCreation(int n);
void printVector(const float *vec, int n);
float elapsed_time_microsec(struct timespec *begin, struct timespec *end,
                            unsigned long *sec, unsigned long *nsec);
float standardDeviation(float times[], int numSamples);
float Average(float *times, int numSamples);
long requiredSampleSize(float sd, float mean);

#endif //ACA_LAB3_UTIL_H
