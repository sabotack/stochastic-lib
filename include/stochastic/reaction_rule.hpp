#ifndef REACTION_RULE_HPP
#define REACTION_RULE_HPP

#include "combination.hpp"
#include "reaction_rate.hpp"

namespace stochastic
{
    struct ReactionRule {
        Combination input;
        Combination output;
        double rate;

        ReactionRule(Combination in, const double r, Combination out)
            : input(std::move(in)), output(std::move(out)), rate(r)
        {
        }
    };

    std::ostream& operator<<(std::ostream& os, const ReactionRule& rule);

    /* RQ1: The library should overload operators to support the reaction rule typesetting directly
     * in C++ code. */
    inline ReactionRule operator>>=(const ReactionRate& rr, const Combination& out)
    {
        return ReactionRule{rr.input, rr.rate, out};
    }

    inline ReactionRule operator>>=(const ReactionRate& rr, const Reactant& out)
    {
        return ReactionRule{rr.input, rr.rate, Combination{out}};
    }
}  // namespace stochastic

#endif  // REACTION_RULE_HPP
