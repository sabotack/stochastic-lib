#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <future>
#include <random>
#include <utility>

#include "utils.hpp"
#include "vessel.hpp"

namespace stochastic {
    class Simulator {
        Vessel vessel;
        std::random_device rd{};

        double computeDelay(const ReactionRule& rule);

    public:
        explicit Simulator(Vessel  vessel) : vessel(std::move(vessel)) {};

        void simulate(double endtime, const StateObserver &observer);

        template <typename ObserverFactory>
        void simulateMultiple (const int simCount, const double endtime, ObserverFactory getObserver) {
            std::vector<std::future<void>> futures{};

            for (int i = 0; i < simCount; i++) {
                futures.emplace_back(std::async(std::launch::async, [=]() {
                    stochastic::Simulator sim{this->vessel};
                    auto observer = getObserver();
                    sim.simulate(endtime, observer);
                }));
            }

            for (auto& f : futures) f.get();
        }
    };
}


#endif //SIMULATOR_HPP
