#ifndef LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H
#define LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H

#include "matrix_multiplier_test.h"
#include <omp.h>

class optimized_parallel_matrix_multiplier_test : public matrix_multiplier_test {

public:
    optimized_parallel_matrix_multiplier_test(unsigned int n) : matrix_multiplier_test(n, true) {
    }

    void multiply() {
        omp_set_dynamic(0);
        omp_set_num_threads(4);
        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                C[i * n + j] = 0;
                for (int k = 0; k < n; ++k) {
                    C[i * n + j] += A[i * n + k] * B[j * n + k];
                }
            }
        }
    }
};


#endif //LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H
