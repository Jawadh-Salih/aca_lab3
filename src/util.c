//
// Created by jawadhsr on 2/27/17.
//

#include "../include/util.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// N = (100zs/rx)^2, r - accuracy (5%), s - standard deviation, x - mean, z = 1.960 (95%) - TAKE THE CEIL
/// This function gives the required number of samples to take to achieve
/// accuracy of 5% and 95% confidence
/// \param sd standard deviation
/// \param mean average
/// \return

long requiredSampleSize(float sd, float mean) {
    long N = (long) ceil(((float) 100 * 1.960 * sd) / (5 * mean));
    return N;
}

double mean(double times[], int numSamples) {
    double sum = 0;
    for (int i = 0; i < numSamples; ++i) {
        sum += times[i];
    }
    return (double) sum / numSamples;
}

double standardDeviation(double times[], int numSamples) {
    double u = mean(times,numSamples);
    double variance = 0;
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

int main(){

    printf("Jawadhja");
    example();


}