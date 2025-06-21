#include "vessel.hpp"

stochastic::Reactant stochastic::Vessel::add(
    const std::string &name, const int initialValue, const bool isInternal)
{
    symbols.add(name, initialValue, isInternal);
    return Reactant{name, initialValue};
}

stochastic::ReactionRule &stochastic::Vessel::add(const ReactionRule &rule)
{
    rules.emplace_back(rule);
    return rules.back();
}
