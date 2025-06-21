#include <fstream>
#include <iostream>

#include "examples.hpp"
#include "simulator.hpp"
#include "utils.hpp"

#define ENDTIME 48
#define PLOT_TITLE "CIRCADIAN RHYTHM"
#define PLOT_FILE "plot_circadian_rhythm.png"
#define DOT_FILE "graph_circadian_rhythm.dot"

int main()
{
    const auto vessel = stochastic::circadianRhythm();

    auto times = std::vector<double>{};
    auto values = std::unordered_map<std::string, std::vector<int>>{};
    auto sim = stochastic::Simulator{vessel};

    std::cout << "Simulating...\n";
    sim.simulate(ENDTIME, [&](const double time, const auto& state) {
        times.push_back(time);
        for (const auto& key : state.getKeys()) {
            if (state.isInternal(key)) continue;
            values[key].push_back(state.get(key));
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
