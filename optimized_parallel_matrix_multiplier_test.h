#ifndef LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H
#define LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H

#include "matrix_multiplier_test.h"
#include <omp.h>
#include <stdlib.h>
#include <stdint-gcc.h>

/**
 * Optimized implementation of the parallel matrix multiplication. This class along will result in around 7 times speedup
 * on i7 DualCore machine. For further speedup, compiler level optimizations are required as well.
 */
class optimized_parallel_matrix_multiplier_test : public matrix_multiplier_test {

public:
    explicit optimized_parallel_matrix_multiplier_test(unsigned int n) : matrix_multiplier_test(n) {
    }

    void multiply() override {
        double *transposed_B = new double[n * n];

        // Transposing matrix B for improve caching support by principle of locality
        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                transposed_B[j * n + i] = B[i * n + j];
            }
        }

        #pragma omp parallel for
        for (int_fast16_t i = 0; i < n; ++i) {
            // No parallel for here to reduce thread scheduling overhead
            for (int_fast16_t j = 0; j < n; ++j) {
                // Use a local variable to store the sum for element C(ij) to reduce overhead of cache coherence
                double tmp = 0;
                // int_fast16_t is used since it results in a performance gain when iterating through the loop sequentially
                for (int_fast16_t k = 0; k < n; ++k) {
                    tmp += A[i * n + k] * transposed_B[j * n + k];
                }
                //Finally assign the (ij)th element's value to original matrix C
                C[i * n + j] = tmp;
            }
        }

        free(transposed_B);
    }
};

#endif //LAB_3_4_OPTIMIZED_PARALLEL_MATRIX_MULTIPLIER_TEST_H
