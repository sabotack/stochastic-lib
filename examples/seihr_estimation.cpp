#include <iostream>

#include "examples.hpp"
#include "simulator.hpp"

#define ENDTIME 100
#define NNJ 589'755
#define NDK 5'822'763

/* RQ7: Implement a generic support for (any) user-supplied state observer function object or
 * provide a lazy trajectory generation interface (coroutine). The observer itself should be part by
 * the user/test program and not part of the library. To demonstrate the generic support, estimate
 * the peak of hospitalized agents in Covid-19 example without storing an entire trajectory. Record
 * the peak hospitalization values for population sizes of NNJ and NDK. */
int main()
{
    const auto nnjVessel = stochastic::seihr(NNJ);
    stochastic::Simulator nnjSim{nnjVessel};
    int maxH = 0;
    std::cout << "(NNJ) Simulating...\n";
    nnjSim.simulate(
        ENDTIME, [&](const double _, const auto& state) { maxH = std::max(maxH, state.get("H")); });

    std::cout << "Max H (NNJ): " << maxH << "\n";

    const auto ndkVessel = stochastic::seihr(NDK);
    stochastic::Simulator ndkSim{ndkVessel};
    maxH = 0;
    std::cout << "(NDK) Simulating...\n";
    ndkSim.simulate(
        ENDTIME, [&](const double _, const auto& state) { maxH = std::max(maxH, state.get("H")); });

    std::cout << "Max H (NDK): " << maxH << "\n";
    std::cout << "Finished!\n";
}
