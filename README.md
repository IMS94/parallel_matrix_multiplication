# Comparison between sequential and parallel matrix multiplication and optimizations

## Prerequisites

1. Ubuntu 16.04 Operating System is preferred because it contains all the
required tools pre-installed.
2. CMake 3.5 or above (Install with `sudo apt install cmake`)
3. GNU gcc (5.4.0 - comes with Ubuntu. To install `sudo apt install gcc`)

## CLI
For both sequential vs parallel and optimized scenarios, same code is
used but with different compiler parameters.

Once compiled, this code will result in an executable named `multiplier`.
This executable requires at least 2 arguments.

`./multiplier [sample_size] [S|P|OP]`

- `[sample_size]` is the number of matrices that should be used for each
test.

- `[S|P|OP]` - As the second argument, you should give at least one of
`S(Sequential)`, `P(Parallel non-optimized)` and `OP(Optimized Parallel)`
which will determine which test you want to run.

- If you want run the sequential matrix multiplication test with a sample
size 10, you should run: `./multiplier 10 S` and you will see the
**mean execution time, standard deviation** printed.

- If you want run both sequential matrix multiplication test and the non-optimized
parallel matrix multiplication at the same time, each with a sample
size 10, you should run: `./multiplier 10 S P` and you will see the
results printed accordingly.

## Steps to compile
To run each version/scenario, please follow the following steps.

### Running sequential and non-optimized parallel matrix multiplication

1. Open terminal and go to directory where `CMakeLists.txt` file is at.
2. Create directory **build** inside that: `mkdir build`
3. Go into **build** directory: `cd build`
4. Run CMake with:

    `cmake ..`

    You will see some files have been created inside **build**
    directory like *Makefile*, *CMakeCache.txt*

5. Then run

    `make all`

    You will see the executable `multiplier` has been created in that
    directory.

6. Run the **multipler** with following arguments,

   `./multiplier [sample_size] S P`

   and the execution times will be printed on the terminal.

### Running optimized parallel matrix multiplication

*Note*: If you already have created a `build` directory, first delete it.

1. Open terminal and go to directory where `CMakeLists.txt` file is at.
2. Create directory **build** inside that: `mkdir build`
3. Go into **build** directory: `cd build`
4. Run CMake with:

    `cmake -DCMAKE_BUILD_TYPE=Release ..`

    You will see some files have been created inside **build** directory
    like *Makefile*, *CMakeCache.txt*

5. Then run

    `make all`

    You will see the executable `multiplier` has been created in that
    directory.

6. Run the **multipler** with following arguments,

   `./multiplier [sample_size] OP`

   and the execution times will be printed on the terminal.