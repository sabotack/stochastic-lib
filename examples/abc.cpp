#include <fstream>
#include <iostream>
#include <unordered_map>

#include "examples.hpp"
#include "simulator.hpp"

#define ENDTIME 2000

struct Abc {
    int a;
    int b;
    int c;
};

int main()
{
    std::vector<Abc> abc{
        {100, 0,  1},
        {100, 0,  2},
        {50,  50, 1}
    };

    for (int i = 0; i < abc.size(); i++) {
        const auto n = std::to_string(i + 1);
        const auto vessel = stochastic::abc(abc[i].a, abc[i].b, abc[i].c);

        auto times = std::vector<double>{};
        auto values = std::unordered_map<std::string, std::vector<int>>{};
        auto sim = stochastic::Simulator{vessel};

        std::cout << n << ": Simulating...\n";
        sim.simulate(ENDTIME, [&](const double time, const auto& state) {
            times.push_back(time);
            for (const auto& key : state.getKeys()) {
                if (state.isInternal(key)) continue;
                values[key].push_back(state.get(key));
            }
        });

        std::cout << n << ": Generating plot...\n";
        const auto title = "A=" + std::to_string(abc[i].a) + ", B=" + std::to_string(abc[i].b) + ", C=" + std::to_string(abc[i].c);
        stochastic::plotTimeSeries(title, "plot_abc_" + n + ".png", times, values);

        std::ofstream file("graph_abc_" + n + ".dot");
        if (!file) {
            throw std::runtime_error("Failed to open output file.");
        }
        std::cout << n << ": Generating dot graph...\n";
        stochastic::exportToDot(file, vessel);
    }
    std::cout << "Finished!\n";
}
