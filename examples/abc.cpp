
#include <fstream>

#include "stochastic_lib.hpp"
#include "examples.hpp"

struct Abc {
    int a;
    int b;
    int c;
};

int main() {
    std::vector<Abc> abc {{100, 0, 1}, {100, 0, 2}, {50, 50, 1}};

    for (int i = 0; i < abc.size(); i++) {
        const auto vessel = stochastic::abc(abc[i].a, abc[i].b, abc[i].c);

        auto times = std::vector<double>{};
        auto values = std::unordered_map<std::string, std::vector<int>>{};
        auto sim = stochastic::Simulator{vessel};

        sim.simulate(2000, [&](const double time, const auto& state) {
            times.push_back(time);
            for (const auto& key : state.getKeys()) {
                if (state.isInternal(key)) continue;
                values[key].push_back(state.get(key));
            }
        });

        const auto n = std::to_string(i + 1);
        stochastic::plotTimeSeries("ABC " + n , "plot_abc_" + n + ".png", times, values);

        std::ofstream file("graph_abc_" + n + ".dot");
        if (!file) {
            throw std::runtime_error("Failed to open output file.");
        }
        stochastic::exportToDot(file, vessel);
    }

    return 0;
}
