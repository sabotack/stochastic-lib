#include <fstream>

#include "examples.hpp"
#include "simulator.hpp"
#include "utils.hpp"

int main() {
    const auto vessel = stochastic::circadianRhythm();

    auto times = std::vector<double>{};
    auto values = std::unordered_map<std::string, std::vector<int>>{};
    auto sim = stochastic::Simulator{vessel};

    sim.simulate(50, [&](const double time, const auto& state) {
        times.push_back(time);
            for (const auto& key : state.getKeys()) {
                if (state.isInternal(key)) continue;
                values[key].push_back(state.get(key));
            }
    });

    stochastic::plotTimeSeries("CIRCADIAN RHYTHM", "plot_circadian_rhythm.png", times, values);

    std::ofstream file("graph_circadian_rhythm.dot");
    if (!file) {
        throw std::runtime_error("Failed to open output file.");
    }
    stochastic::exportToDot(file, vessel);

    return 0;
}
