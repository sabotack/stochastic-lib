#include "vessel.hpp"

using namespace stochastic;

Reactant Vessel::add(const std::string &name, const int initialValue, const bool isInternal) {
    symbols.add(name, initialValue, isInternal);
    return Reactant{name, initialValue};
}

ReactionRule Vessel::add(const ReactionRule &rule) {
    rules.push_back(rule);
    return ReactionRule{rule};
}



