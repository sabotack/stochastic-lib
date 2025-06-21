#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <future>
#include <random>
#include <utility>

#include "utils.hpp"
#include "vessel.hpp"

namespace stochastic
{
    class Simulator
    {
        Vessel vessel;
        std::random_device rd{};

        static double computeDelay(
            const ReactionRule& rule, const std::shared_ptr<SymbolTable<std::string, int>>& symbols,
            std::mt19937& gen);
        static void applyReaction(
            const ReactionRule& rule,
            const std::shared_ptr<SymbolTable<std::string, int>>& symbols);

       public:
        explicit Simulator(Vessel vessel) : vessel(std::move(vessel)) {};

        void simulate(double endtime, const StateObserver& observer);

        void simulateMultiple(int simCount, double endtime, const ThreadObserver& observer);
    };
}  // namespace stochastic

#endif  // SIMULATOR_HPP
