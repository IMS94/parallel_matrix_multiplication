#ifndef LAB_3_4_PARALLEL_MATRIX_MULTIPLIER_TEST_H
#define LAB_3_4_PARALLEL_MATRIX_MULTIPLIER_TEST_H

#include "matrix_multiplier_test.h"

/**
 * Parallel matrix implementation test class. This class doesn't do any optimization other than using parallel for to
 * multiply matrices.
 */
class parallel_matrix_multiplier_test : public matrix_multiplier_test {

public:
    explicit parallel_matrix_multiplier_test(unsigned int n) : matrix_multiplier_test(n) {
    }

    /**
     * This is the method called by the parent class to measure matrix multiplication time. This class is using two
     * parallel for loops.
     */
    void multiply() {
        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            #pragma omp parallel for
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
