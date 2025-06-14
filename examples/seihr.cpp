#include <fstream>
#include <unordered_map>

#include "examples.hpp"
#include "simulator.hpp"
#include "utils.hpp"

int main() {
    const auto vessel = stochastic::seihr(10000);

    auto times = std::vector<double>{};
    auto values = std::unordered_map<std::string, std::vector<int>>{};
    auto sim = stochastic::Simulator{vessel};

    sim.simulate(100, [&](const double time, const auto& state) {
        times.push_back(time);

        for (const auto& key : state.getKeys()) {
            if (key == "H") {
                values[key + "*1000"].push_back(state.get(key)*1000);
            }
            else {
                values[key].push_back(state.get(key));
            }
        }
    });

    stochastic::plotTimeSeries("SEIHR COVID-19", "plot_seihr_covid19.png", times, values);

    std::ofstream file("graph_seihr_covid19.dot");
    if (!file) {
        throw std::runtime_error("Failed to open output file.");
    }
    stochastic::exportToDot(file, vessel);

    return 0;
}
