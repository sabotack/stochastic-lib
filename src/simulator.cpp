#include <memory>
#include <simulator.hpp>
#include <utils.hpp>

double stochastic::Simulator::computeDelay(
    const ReactionRule& rule, const std::shared_ptr<SymbolTable<std::string, int>>& symbols,
    std::mt19937& gen)
{
    double rate = rule.rate;
    for (const auto& reactant : rule.input.reactants) {
        int value = 0;
        if (symbols->contains(reactant.name)) {
            value = symbols->get(reactant.name);
        }

        if (value <= 0) {
            return std::numeric_limits<double>::infinity();
        }

        rate *= value;
    }

    std::exponential_distribution dist{rate};
    return dist(gen);
}

void stochastic::Simulator::applyReaction(
    const ReactionRule& rule, const std::shared_ptr<SymbolTable<std::string, int>>& symbols)
{
    for (const auto& reactant : rule.input.reactants) {
        symbols->get(reactant.name) -= 1;
    }

    for (const auto& product : rule.output.reactants) {
        symbols->get(product.name) += 1;
    }
}

/* RQ4: Implement the stochastic simulation (Alg. 1) of the system using the reaction rules. */
/* RQ7: Implement a generic support for (any) user-supplied state observer function object or
 * provide a lazy trajectory generation interface (coroutine). The observer itself should be part by
 * the user/test program and not part of the library. To demonstrate the generic support, estimate
 * the peak of hospitalized agents in Covid-19 example without storing an entire trajectory. Record
 * the peak hospitalization values for population sizes of NNJ and NDK. */
void stochastic::Simulator::simulate(const double endtime, const StateObserver& observer)
{
    const auto symbolsPtr = std::make_shared<SymbolTable<std::string, int>>(vessel.getSymbols());
    const auto& rules = vessel.getRules();
    auto gen = std::mt19937(rd());

    auto time = 0.0;
    observer(time, *symbolsPtr);
    while (time <= endtime) {
        std::vector<double> delays{};
        delays.reserve(rules.size());

        for (const auto& rule : rules) {
            delays.push_back(computeDelay(rule, symbolsPtr, gen));
        }

        const auto minDelayIt = std::min_element(delays.begin(), delays.end());
        const auto dt = *minDelayIt;
        if (dt == std::numeric_limits<double>::infinity()) break;

        const auto reactionIdx = std::distance(delays.begin(), minDelayIt);
        applyReaction(rules[reactionIdx], symbolsPtr);

        time += dt;
        observer(time, *symbolsPtr);
    }
}

/* RQ8: Implement support for multiple CPU cores by parallelizing the computation of several
 * simulations at the same time. Estimate the likely (average) value of the hospitalized peak over
 * 100 simulations. */
void stochastic::Simulator::simulateMultiple(
    const int simCount, const double endtime, const ThreadObserver& observer)
{
    std::vector<std::future<void>> futures;
    futures.reserve(simCount);

    for (int i = 0; i < simCount; ++i) {
        futures.push_back(std::async(std::launch::async, [this, endtime, i, &observer]() {
            this->simulate(
                endtime, [&](double time, const auto& state) { observer(i, time, state); });
        }));
    }

    for (auto& fut : futures) {
        fut.get();
    }
}
