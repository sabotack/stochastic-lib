#include <iostream>

#include "examples.hpp"
#include "simulator.hpp"

#define NNJ 589'755
#define NDK 5'822'763
#define ENDTIME 100

int main() {

    const auto v = stochastic::seihr(NNJ);
    stochastic::Simulator s{v};
    int mH = 0;

    s.simulateMultiple(2, ENDTIME, [&]() {
        auto maxH = std::make_shared<int>(0);
        return [=](double, const auto& state) {
            *maxH = std::max(*maxH, state.get("H"));
        };
    });

    // s.simulate(ENDTIME, [&](const double _, const auto& state) {
    //     mH = std::max(mH, state.get("H"));
    // });

    return 0;
    const auto nnjVessel = stochastic::seihr(NNJ);
    stochastic::Simulator nnjSim{nnjVessel};
    int maxH = 0;
    nnjSim.simulate(ENDTIME, [&](const double _, const auto& state) {
        maxH = std::max(maxH, state.get("H"));
    });

    std::cout << "Max H (NNJ): " << maxH << "\n";

    const auto ndkVessel = stochastic::seihr(NDK);
    stochastic::Simulator ndkSim{ndkVessel};
    maxH = 0;
    nnjSim.simulate(ENDTIME, [&](const double _, const auto& state) {
       maxH = std::max(maxH, state.get("H"));
    });

    std::cout << "Max H (NDK): " << maxH << "\n";
}
