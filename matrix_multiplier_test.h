#ifndef LAB_3_4_MATRIX_MULTIPLIER_TEST_H
#define LAB_3_4_MATRIX_MULTIPLIER_TEST_H

#include <iostream>
#include <random>
#include <sys/time.h>

using namespace std;

/**
 * This is the main class of the matrix multiplication tests. This class generates a n*n matrix once 'n' is given with
 * random values as elements.
 */
class matrix_multiplier_test {
private:
    double elapsed_time = 0;

    void print_matrix(double *matrix) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << matrix[i * n + j] << "\t";
            }
            cout << endl;
        }
    }

    /**
     * Populates matrices A and B with random values.
     */
    void populate_matrix() {
        random_device rand_device;
        mt19937 generator(rand_device());
        uniform_real_distribution<double> distribution(numeric_limits<float>::min(), numeric_limits<float>::max());

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i * n + j] = distribution(generator);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                B[i * n + j] = distribution(generator);
            }
        }
    }

protected:
    unsigned int n;
    double *A;
    double *B;
    double *C;

public:
    matrix_multiplier_test(unsigned int n) {
        this->n = n;

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

    /**
     * This is the method to be called to run the test. This will call method multiply() of subclasses and measure the
     * time for multiply method to complete.
     */
    void run_test() {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        // Time to complete following method is measured
        multiply();
        gettimeofday(&end, NULL);
        double delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        elapsed_time = delta;
    }

    /**
     * Sub classes should implement this method with the corresponding matrix multiplication technique. Time taken to
     * complete this method is taken as the time for matrix multiplication.
     */
    virtual void multiply()= 0;

    void print_result(bool print_matrices) {
        if (print_matrices) {
            cout << "\n\nMatrix A:" << endl;
            print_matrix(A);
            cout << "\n\nMatrix B:" << endl;
            print_matrix(B);
            cout << "\n\nMatrix C (=A x B) :" << endl;
            print_matrix(C);
            cout << endl;
        }

        cout << "\nElapsed Time : " << elapsed_time << "\n\n" << endl;
    }

    double getElapsed_time() const {
        return elapsed_time;
    }
};


#endif //LAB_3_4_MATRIX_MULTIPLIER_TEST_H
