#ifndef LAB_3_4_MATRIX_MULTIPLIER_TEST_H
#define LAB_3_4_MATRIX_MULTIPLIER_TEST_H

#include <iostream>
#include <random>
#include <sys/time.h>

using namespace std;

class matrix_multiplier_test {
private:
    double elapsed_time = 0;

    void print_matrix(double *matrix, bool transposed) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << matrix[transposed ? j * n + i : i * n + j] << "\t";
            }
            cout << endl;
        }
    }

    void populate_matrix() {
        random_device rand_device;
        mt19937 generator(rand_device());
        uniform_real_distribution<double> distribution(numeric_limits<float>::min(), numeric_limits<float>::max());

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i * n + j] = distribution(generator);
            }
        }

        if (optimized) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    B[j * n + i] = distribution(generator);
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    B[i * n + j] = distribution(generator);
                }
            }
        }
    }

protected:
    unsigned int n;
    bool optimized = false;
    double *A;
    double *B;
    double *C;

public:
    matrix_multiplier_test(unsigned int n, bool optimized) {
        this->n = n;
        this->optimized = optimized;

        A = new double[n * n];
        B = new double[n * n];
        C = new double[n * n];

        populate_matrix();
    }

    ~matrix_multiplier_test() {
        delete[] A;
        delete[] B;
        delete[] C;
    }

    void run_test() {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        multiply();
        gettimeofday(&end, NULL);
        double delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        elapsed_time = delta;
    }

    virtual void multiply()= 0;

    void print_result(bool print_matrices) {
        if (print_matrices) {
            cout << "\n\nMatrix A:" << endl;
            print_matrix(A, false);
            cout << "\n\nMatrix B:" << endl;
            print_matrix(B, optimized);
            cout << "\n\nMatrix C (=A x B) :" << endl;
            print_matrix(C, false);
            cout << endl;
        }

        cout << "\nElapsed Time : " << elapsed_time << "\n\n" << endl;
    }

    double getElapsed_time() const {
        return elapsed_time;
    }
};


#endif //LAB_3_4_MATRIX_MULTIPLIER_TEST_H
