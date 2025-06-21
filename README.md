
# Stochastic Simulation Library
A C++ library for simulating stochastic systems using the **Doob–Gillespie algorithm**.

Developed as an assignment for the *Selected Topics in Programming* (sP) course at Aalborg University (AAU).

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
- cmake/ - *cmake files for compiling test libraries*
- examples/ - *Demonstration of the simulation library*
- external/ - *External libraries*
- include/ - *Public headers for the library*
- output/ - *Graphs and plots*
- src/ - *Simulation library implementation*
- tests/ - *Unit tests and benchmarks*

## Peak Hospitalization Estimation
Peak hospitalization values for populations of sizes NNJ and NDK (recorded through single run of `seihr_estimation.cpp`):

- NNJ H-peak: 118
- NDK H-peak: 1221


Average estimated hospitalization peak for running `seihr_multiple.cpp`:

- Estimated average H-peak: 3.62
