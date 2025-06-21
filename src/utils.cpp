#include <matplotlibcpp.h>

#include <iostream>
#include <utils.hpp>

namespace plt = matplotlibcpp;

/* RQ6: Display simulation trajectories of how the amounts change. External tools/libraries can be
 * used to visualize. */
void stochastic::plotTimeSeries(
    const std::string& title, const std::string& fileName, const std::vector<double>& times,
    const std::unordered_map<std::string, std::vector<int>>& values)
{
    if (times.empty() || values.empty()) {
        throw std::invalid_argument("Empty time vector or values.");
    }

    for (const auto& [key, series] : values) {
        if (series.size() != times.size()) {
            throw std::invalid_argument("Series size does not match time vector size.");
        }

        std::vector<double> s(series.begin(), series.end());
        plt::plot(
            times, s,
            {
                {"label", key}
        });
    }

    plt::title(title);
    plt::xlabel("Time");
    plt::ylabel("Quantity");
    plt::legend();
    plt::save(fileName);
    plt::clf();
}

void stochastic::printVesselState(const SymbolTable<std::string, int>& symbols)
{
    std::cout << "Vessel state of symbols:\n";
    for (const auto& key : symbols.getKeys()) {
        std::cout << "  " << key << ": " << symbols.get(key) << '\n';
    }
}

/* RQ2: Provide pretty-printing of the reaction network in a) human readable format and b) network
 * graph (e.g. Fig. 4). */
void stochastic::exportToDot(std::ostream& os, const Vessel& vessel)
{
    const auto& rules = vessel.getRules();
    const auto& symbols = vessel.getSymbols();
    os << "digraph {\n";

    for (const auto& symbol : symbols.getKeys(true)) {
        os << " " << symbol << " [label=\"" << symbol
           << "\", shape=box, style=filled, fillcolor=cyan];\n";
    }

    int counter = 0;
    for (const auto& rule : rules) {
        auto reactionNode = "r" + std::to_string(counter++);

        os << " " << reactionNode << " [label=\"" << rule.rate
           << "\", shape=oval, style=filled, fillcolor=yellow];\n";

        for (const auto& in : rule.input.reactants) {
            os << " " << in.name << " -> " << reactionNode << ";\n";
        }

        for (const auto& out : rule.output.reactants) {
            if (!symbols.isInternal(out.name))
                os << " " << reactionNode << " -> " << out.name << ";\n";
        }
    }

    os << "}\n";
}
