
# Stochastic Simulation Library
A C++ library for simulating stochastic systems using the **Doob–Gillespie algorithm**.

> [!NOTE]
> Developed as an assignment for the *Selected Topics in Programming* (sP) course at Aalborg University (AAU).

> [!IMPORTANT]
> All [requirements](#project-requirements) defined as part of the description of the assignment have been fulfilled! Additionally, the `examples` directory provides usage examples of the library using three different models (abc, circadian_rhythm, and seihr).

## Build Requirements
- C++23-compatible compiler
- CMake ≥ 3.31
- Python 3.10 (with NumPy and matplotlib for plotting with`matplotlib-cpp`)

## Build
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Project Structure
```
├── cmake/         # cmake files for compiling test libraries
├── examples/      # Demonstration of the simulation library
├── external/      # External libraries
├── include/       # Public headers for the library
├── output/        # Graphs and plots
├── src/           # Simulation library implementation
├── tests/         # Unit tests and benchmarks
```

## Project Requirements
The following set of requirements are shortened versions of the requirements provided with the assignment description.

1. Overload C++ operators for intuitive reaction rule syntax.
2. Support text and DOT-format output for reaction networks.
3. Implement a generic symbol table with error handling.
4. Simulate reactions using the Doob–Gillespie algorithm.
5. Include ABC, circadian rhythm, and SEIHR example models.
6. Output time-series data for plotting trajectories.
7. Allow custom observer functions or lazy evaluation.
8. Enable parallel execution for multiple simulations.
9. Provide unit tests for all core components.
10. Benchmark performance for different simulation setups.

## Peak Hospitalization Estimation
Peak hospitalization values for populations of sizes NNJ and NDK (recorded through single run of `seihr_estimation.cpp`):

- NNJ H-peak: 118
- NDK H-peak: 1221

Average estimated hospitalization peak for running `seihr_multiple.cpp`:

- Estimated average H-peak: 3.62
