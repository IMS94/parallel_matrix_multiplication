#ifndef LAB_3_4_PARALLEL_MATRIX_MULTIPLIER_TEST_H
#define LAB_3_4_PARALLEL_MATRIX_MULTIPLIER_TEST_H

#include "matrix_multiplier_test.h"

class parallel_matrix_multiplier_test : public matrix_multiplier_test {

public:
    parallel_matrix_multiplier_test(unsigned int n) : matrix_multiplier_test(n) {

    }

    void multiply() {
        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                C[i * n + j] = 0;
                for (int k = 0; k < n; ++k) {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
};


#endif //LAB_3_4_PARALLEL_MATRIX_MULTIPLIER_TEST_H
