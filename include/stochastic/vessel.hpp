#ifndef VESSEL_HPP
#define VESSEL_HPP

#include <vector>

#include "reaction_rule.hpp"
#include "symbol_table.hpp"

namespace stochastic
{
    class Vessel
    {
        SymbolTable<std::string, int> symbols{};
        std::vector<ReactionRule> rules{};

       public:
        Vessel() = default;

        [[nodiscard]] const SymbolTable<std::string, int>& getSymbols() const { return symbols; }
        [[nodiscard]] const std::vector<ReactionRule>& getRules() const { return rules; }

        Reactant add(const std::string& name, int initialValue, bool isInternal = false);
        ReactionRule& add(const ReactionRule& rule);
    };
}  // namespace stochastic

#endif  // VESSEL_HPP
