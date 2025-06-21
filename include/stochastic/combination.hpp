#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <vector>

#include "reactant.hpp"

namespace stochastic
{
    struct Combination {
        std::vector<Reactant> reactants{};

        Combination(const Reactant &reactant) { reactants.push_back(reactant); };

        /* RQ1: The library should overload operators to support the reaction rule typesetting
         * directly in C++ code. */
        Combination &operator+(const Reactant &other)
        {
            reactants.push_back(other);
            return *this;
        }
    };

    /* RQ1: The library should overload operators to support the reaction rule typesetting directly
     * in C++ code. */
    inline Combination operator+(const Reactant &r1, const Reactant &r2)
    {
        return Combination(r1) + r2;
    }
}  // namespace stochastic

#endif  // COMBINATION_HPP
