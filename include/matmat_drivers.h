//
// Created by krv on 3/10/17.
//

#ifndef ACA_LAB3_MATMAT_DRIVERS_H
#define ACA_LAB3_MATMAT_DRIVERS_H

void driveMatMatCPU(const float **mat_a, const float **mat_b, float **mat_c, int n);

void driveMatMat_SSE(const float **mat_a, const float **mat_b, float **mat_c, int n);

#endif //ACA_LAB3_MATMAT_DRIVERS_H
