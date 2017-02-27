//
// Created by jawadhsr on 2/27/17.
//
#include <stdio.h>
#include <pmmintrin.h>
#include "util.h"
static void
matvec_simple ( int n , float vec_c [ n ] ,
                const float mat_a [ n ] [ n ] , const float vec_b [ n ] )
{
    for ( int i = 0; i < n ; i ++)
        for ( int j = 0; j < n ; j ++)
            vec_c [ i ] += mat_a [ i ] [ j ] * vec_b [ j ] ;
}

static void matvec_unrolled(int n,float vec_c[n], const float mat_a[n][n], const float vec_b[n]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j+=4){
            vec_c[i] += mat_a[i][j]*vec_b[j]
                        + mat_a[i][j+1]*vec_b[j+1]
                        + mat_a[i][j+2]*vec_b[j+2]
                        + mat_a[i][j+3]*vec_b[j+3];
        }
    }
}


void example(void){
    printf("adsdefwa");
}