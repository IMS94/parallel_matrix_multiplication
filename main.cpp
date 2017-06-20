
#define STEP 200
#define N_START 200
#define N_STOP 2000
#define ITERATIONS 10

#include <iostream>
#include "sequential_matrix_multiplier_test.h"
#include "parallel_matrix_multiplier_test.h"

using namespace std;

void calc_mean_and_stdv(vector<double> times);

int main() {

    for (int i = N_START; i <= N_STOP; i += STEP) {
        cout << "\n\nN = " << i << "\n" << endl;
        vector<double> serial_times;
        vector<double> parallel_times;

        for (int j = 0; j < ITERATIONS; ++j) {
            cout << "\nRunning the sequential test\n" << endl;
            sequential_matrix_multiplier_test serial_test = sequential_matrix_multiplier_test(i);
            serial_test.run_test();
            serial_test.print_result(false);
            serial_times.push_back(serial_test.getElapsed_time());

            cout << "\nRunning the parallel test" << endl;
            parallel_matrix_multiplier_test parallel_test = parallel_matrix_multiplier_test(i);
            parallel_test.run_test();
            parallel_test.print_result(false);
            parallel_times.push_back(parallel_test.getElapsed_time());
        }
        cout << "\nMean and Standard Deviation\n" << endl;
        calc_mean_and_stdv(serial_times);
        calc_mean_and_stdv(parallel_times);
        break;
    }

    return 0;
}

void calc_mean_and_stdv(vector<double> times) {
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double mean = sum / times.size();

    double sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / times.size() - mean * mean);
    double n = std::pow(((100 * 1.96 * stdev) / (5 * mean)), 2);
    cout << "Mean\t: " << mean * 1000 << endl;
    cout << "std\t: " << stdev * 1000 << endl;
    cout << "n\t: " << n << endl;
}