#ifndef LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H
#define LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H

#include "matrix_multiplier_test.h"
#include <omp.h>
#include <stdlib.h>
#include <stdint-gcc.h>

class optimized_parallel_matrix_multiplier_test : public matrix_multiplier_test {

public:
    explicit optimized_parallel_matrix_multiplier_test(unsigned int n) : matrix_multiplier_test(n) {
    }

    void multiply() override {
        double *transposed_B = new double[n * n];

        // Transposing
        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                transposed_B[j * n + i] = B[i * n + j];
            }
        }

        #pragma omp parallel for
        for (int_fast16_t i = 0; i < n; ++i) {
            for (int_fast16_t j = 0; j < n; ++j) {
                double tmp = 0;
                for (int_fast16_t k = 0; k < n; ++k) {
                    tmp += A[i * n + k] * transposed_B[j * n + k];
                }
                C[i * n + j] = tmp;
            }
        }

        free(transposed_B);
    }
};

#endif //LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H
