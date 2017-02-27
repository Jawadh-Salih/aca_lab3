//
// Created by jawadhsr on 2/27/17.
//

#ifndef ACA_LAB3_UTIL_H
#define ACA_LAB3_UTIL_H

void example(void);
static void matvec_simple(int n, float vec_c[n],const float mat_a[n][n] , const float vec_b[n]);
static void matvec_unrolled(int n, float vec_c[n],const float mat_a[n][n] , const float vec_b[n]);

#endif //ACA_LAB3_UTIL_H
