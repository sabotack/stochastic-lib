#include <fstream>
#include <iostream>
#include <unordered_map>

#include "examples.hpp"
#include "simulator.hpp"
#include "utils.hpp"

#define ENDTIME 100
#define PLOT_TITLE "SEIHR COVID-19"
#define PLOT_FILE "plot_seihr_covid19.png"
#define DOT_FILE "graph_seihr_covid19.dot"

int main()
{
    const auto vessel = stochastic::seihr(10000);

    auto times = std::vector<double>{};
    auto values = std::unordered_map<std::string, std::vector<int>>{};
    auto sim = stochastic::Simulator{vessel};

    std::cout << "Simulating...\n";
    sim.simulate(ENDTIME, [&](const double time, const auto& state) {
        times.push_back(time);

        for (const auto& key : state.getKeys()) {
            if (key == "H") {
                values[key + "*1000"].push_back(state.get(key) * 1000);
            } else {
                values[key].push_back(state.get(key));
            }
        }
    });

    std::cout << "Generating plot...\n";
    stochastic::plotTimeSeries(PLOT_TITLE, PLOT_FILE, times, values);

    std::ofstream file(DOT_FILE);
    if (!file) {
        throw std::runtime_error("Failed to open output file.");
    }
    std::cout << "Generating dot graph...\n";
    stochastic::exportToDot(file, vessel);
    std::cout << "Finished!\n";
}
