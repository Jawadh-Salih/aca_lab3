//
// Created by jawadhsr on 2/27/17.
//

void matvec_unrolled_auto(int n, float *vec_c, const float **mat_a, const float *vec_b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j += 4) {
            vec_c[i] += mat_a[i][j] * vec_b[j]
                        + mat_a[i][j + 1] * vec_b[j + 1]
                        + mat_a[i][j + 2] * vec_b[j + 2]
                        + mat_a[i][j + 3] * vec_b[j + 3];
        }
    }
}