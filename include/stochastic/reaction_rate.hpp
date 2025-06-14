#ifndef REACTION_RATE_HPP
#define REACTION_RATE_HPP
#include <utility>

#include "combination.hpp"

namespace stochastic {
    struct ReactionRate {
        Combination input;
        double rate;

        ReactionRate(Combination input, const double rate)
            : input(std::move(input)), rate(rate) {}
    };

    inline ReactionRate operator>>(const Combination& c, const double r) {
        return ReactionRate{c, r};
    }
}


#endif //REACTION_RATE_HPP
