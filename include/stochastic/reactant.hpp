#ifndef REACTANT_HPP
#define REACTANT_HPP

#include <string>
#include <utility>

namespace stochastic
{
    struct Reactant {
        std::string name;
        int quantity;

        Reactant(std::string name, const int quantity)
            : name(std::move(name)), quantity(quantity) {};
    };
}  // namespace stochastic

#endif  // REACTANT_HPP
