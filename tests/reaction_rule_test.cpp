#include "reaction_rule.hpp"

#include <sstream>

#include "doctest/doctest.h"

TEST_SUITE("operator<<")
{
    TEST_CASE("Formats simple ReactionRule correctly")
    {
        stochastic::ReactionRule rule{
            stochastic::Reactant("A", 1) + stochastic::Reactant("B", 1) >> 0.25 >>=
            stochastic::Reactant("C", 1)};
        std::ostringstream oss;
        oss << rule;

        CHECK(oss.str() == "A + B >> 0.25 >>= C");
    }
}
