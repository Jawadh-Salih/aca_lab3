//
// Created by krv on 2/28/17.
//

#ifndef ACA_LAB3_MATVEC_H
#define ACA_LAB3_MATVEC_H

void  matvec_simple ( int n , float * vec_c , const float ** mat_a , const float * vec_b);
void matvec_unrolled(int n,float *vec_c, const float** mat_a, const float *vec_b);

void matvec_unrolled_sse(int n, float *vec_c, const float mat_a[n][n], const float vec_b[n]);

#endif //ACA_LAB3_MATVEC_H
