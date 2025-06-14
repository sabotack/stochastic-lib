
#include <memory>

#include "simulator.hpp"
#include "utils.hpp"


namespace stochastic {
    double Simulator::computeDelay(const ReactionRule &rule) {


    }

    void Simulator::simulate(const double endtime, const StateObserver &observer) {
        auto symbolsPtr = std::make_shared<SymbolTable<std::string, int>>(vessel.getSymbols());
        const auto& rules = vessel.getRules();
        auto gen = std::mt19937(rd());


        auto time = 0.0;
        observer(time, *symbolsPtr);
        while (time <= endtime) {
            std::vector<double> delays{};

            for (const auto& rule : rules) {
                double rate = rule.rate;
                for (const auto& reactant : rule.input.reactants) {
                    if (!symbolsPtr->contains(reactant.name) || symbolsPtr->get(reactant.name) <= 0) {
                        rate = 0;
                        break;
                    }
                    rate *= symbolsPtr->get(reactant.name);
                }

                if (rate == 0) {
                    delays.push_back(std::numeric_limits<double>::infinity());
                }
                else {
                    std::exponential_distribution dist{rate};
                    delays.push_back(dist(gen));
                }
            }

            auto minDelay = std::min_element(delays.begin(), delays.end());
            const auto reactionIdx = std::distance(delays.begin(), minDelay);
            const auto dt = *minDelay;

            if (dt == std::numeric_limits<double>::infinity()) break;
            time += dt;

            const auto& rule = rules[reactionIdx];
            for (const auto& r : rule.input.reactants) {
                symbolsPtr->get(r.name) -= 1;
            }
            for (const auto& r : rule.output.reactants) {
                symbolsPtr->get(r.name) += 1;
            }

            observer(time, *symbolsPtr);
        }

        // printVesselState(*symbolsPtr);
    }

}
