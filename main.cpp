
#define STEP 200
#define N_START 200
#define N_STOP 2000
#define ITERATIONS 20

#include <iostream>
#include "sequential_matrix_multiplier_test.h"
#include "parallel_matrix_multiplier_test.h"
#include "optimized_parallel_matrix_multiplier_test.h"

using namespace std;

int calc_mean_and_stdv(vector<double> times);

double mean(vector<double> times);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "At least two arguments are required. \n\t./{executable} [iterations] [S|P|OP]" << endl;
        exit(1);
    }

    vector<int> sample_sizes_serial;
    vector<int> sample_sizes_parallel;
    vector<int> sample_sizes_optimized;

    for (unsigned int i = N_START; i <= N_STOP; i += STEP) {
        cout << "================ N = " << i << " ==========" << endl;
        vector<double> serial_times;
        vector<double> parallel_times;
        vector<double> optimized_times;

        for (int k = 2; k < argc; ++k) {
            string arg = argv[k];
            for (unsigned int j = 0; j < ITERATIONS; ++j) {
                if (arg == "S") {
                    sequential_matrix_multiplier_test serial_test = sequential_matrix_multiplier_test(i);
                    serial_test.run_test();
                    serial_times.push_back(serial_test.getElapsed_time());
                }

                if (arg == "P") {
                    parallel_matrix_multiplier_test parallel_test = parallel_matrix_multiplier_test(i);
                    parallel_test.run_test();
                    parallel_times.push_back(parallel_test.getElapsed_time());
                }

                if (arg == "OP") {
                    optimized_parallel_matrix_multiplier_test optimized_test =
                            optimized_parallel_matrix_multiplier_test(i);
                    optimized_test.run_test();
                    optimized_times.push_back(optimized_test.getElapsed_time());
                }
            }
        }

        for (int k = 2; k < argc; ++k) {
            string arg = argv[k];
            if (arg == "S") {
                cout << "\t Serial Test" << endl;
                int serial_n = calc_mean_and_stdv(serial_times);
                sample_sizes_serial.push_back(serial_n);
            }

            if (arg == "P") {
                cout << "\t Parallel Test" << endl;
                int parallel_n = calc_mean_and_stdv(parallel_times);
                cout << "\t\tSpeedup \t: " << mean(serial_times) / mean(parallel_times) << "\n" << endl;
                sample_sizes_parallel.push_back(parallel_n);
            }

            if (arg == "OP") {
                cout << "\t Optimized Parallel Test" << endl;
                int optimized_n = calc_mean_and_stdv(optimized_times);
                cout << "\t\tSpeedup \t: " << mean(serial_times) / mean(optimized_times) << "\n" << endl;
                sample_sizes_optimized.push_back(optimized_n);
            }
        }
    }

    for (int a:sample_sizes_serial) {
        cout << a << " ";
    }
    cout << endl;
    for (int a:sample_sizes_parallel) {
        cout << a << " ";
    }
    cout << endl;
    for (int a:sample_sizes_optimized) {
        cout << a << " ";
    }

    cout << endl;
    return 0;
}

int calc_mean_and_stdv(vector<double> times) {
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double mean = sum / times.size();

    double sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / times.size() - mean * mean);
    double n = std::pow(((100 * 1.96 * stdev) / (5 * mean)), 2);

    cout << "\t-------------------------------------" << endl;
    cout << "\tMean\t: " << mean << endl;
    cout << "\tstd\t\t: " << stdev << endl;
    cout << "\tn\t\t: " << n << endl;
    cout << "\t-------------------------------------" << endl;

    return (int) n;
}

double mean(vector<double> times) {
    return std::accumulate(times.begin(), times.end(), 0.0) / times.size();
}