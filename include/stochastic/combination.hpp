#ifndef COMBINATION_HPP
#define COMBINATION_HPP
#include <vector>

#include "reactant.hpp"

namespace stochastic {
    struct Combination {
        std::vector<Reactant> reactants{};

        Combination(const Reactant &reactant) {
            reactants.push_back(reactant);
        };

        Combination& operator+(const Reactant &other) {
            reactants.push_back(other);
            return *this;
        }

    };

    inline Combination operator+(const Reactant &r1, const Reactant &r2) {
        return Combination(r1) + r2;
    }
}

#endif //COMBINATION_HPP
