#include <iostream>
#include "utils.hpp"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void stochastic::plotTimeSeries(
    const std::string& title,
    const std::string& fileName,
    const std::vector<double>& times,
    const std::unordered_map<std::string, std::vector<int>>& values
) {
    for (const auto& [key, series] : values) {
        std::vector<double> s(series.begin(), series.end());
        plt::plot(times, s, {{"label", key}});
    }

    plt::title(title);
    plt::xlabel("Time");
    plt::ylabel("Reactant");
    plt::legend();
    plt::save(fileName);
    plt::clf();
}

void stochastic::printVesselState(const SymbolTable<std::string, int> &symbols) {
    std::cout << "Final state of symbols:\n";
    for (const auto& key : symbols.getKeys()) {
        std::cout << "  " << key << ": " << symbols.get(key) << '\n';
    }
}

void stochastic::exportToDot(std::ostream &os, const Vessel& vessel) {
    const auto& rules = vessel.getRules();
    os << "digraph {\n";

    for (const auto& symbol : vessel.getSymbols().getKeys(true)) {
        os << " " << symbol << " [label=\"" << symbol << "\", shape=box, style=filled, fillcolor=cyan];\n";
    }

    int counter = 0;
    for (const auto& rule : rules) {
        auto reactionNode = "r" + std::to_string(counter++);

        os << " " << reactionNode << " [label=\"" << rule.rate << "\", shape=oval, style=filled, fillcolor=yellow];\n";

        for (const auto& in : rule.input.reactants) {
            os << " " << in.name << " -> " << reactionNode << ";\n";
        }

        for (const auto& out : rule.output.reactants) {
            os << " " << reactionNode << " -> " << out.name << ";\n";
        }
    }

    os << "}\n";
}
