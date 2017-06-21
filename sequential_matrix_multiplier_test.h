#ifndef LAB_3_4_SEQUENTIAL_MATRIX_MULTIPLIER_H

#define LAB_3_4_SEQUENTIAL_MATRIX_MULTIPLIER_H

#include <zconf.h>
#include <iostream>
#include <random>
#include "matrix_multiplier_test.h"

using namespace std;

class sequential_matrix_multiplier_test : public matrix_multiplier_test {
public:
    sequential_matrix_multiplier_test(unsigned int n) : matrix_multiplier_test(n, false) {
    }

    void multiply() {
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


#endif //LAB_3_4_SEQUENTIAL_MATRIX_MULTIPLIER_H
