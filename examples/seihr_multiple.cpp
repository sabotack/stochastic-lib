#include <iostream>

#include "examples.hpp"
#include "simulator.hpp"

#define ENDTIME 100
#define NSIM 100

int main()
{
    const auto seihr = stochastic::seihr(10000);
    stochastic::Simulator sim(seihr);

    std::vector peakValues(NSIM, 0);
    std::cout << "Running " << NSIM << " simulations...\n";
    ;
    sim.simulateMultiple(NSIM, ENDTIME, [&](const int simIndex, double, const auto& state) {
        if (state.contains("H")) {
            peakValues[simIndex] = std::max(peakValues[simIndex], state.get("H"));
        }
    });

    const double avg = std::accumulate(peakValues.begin(), peakValues.end(), 0.0) /
                       static_cast<double>(peakValues.size());
    std::cout << "AVERAGE PEAK-H: " << avg << "\n";
    std::cout << "Finished!\n";
}
