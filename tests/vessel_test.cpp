#include "vessel.hpp"

#include "doctest/doctest.h"

TEST_SUITE("Vessel::add")
{
    TEST_CASE("Correctly adds reactant")
    {
        stochastic::Vessel vessel;
        auto reactant = vessel.add("A", 10);

        CHECK(vessel.getSymbols().contains("A"));
        CHECK(vessel.getSymbols().get("A") == 10);
        CHECK(reactant.name == "A");
    }

    TEST_CASE("Correctly marks internal symbol")
    {
        stochastic::Vessel vessel;
        vessel.add("X", 5, true);

        CHECK(vessel.getSymbols().isInternal("X"));
    }

    TEST_CASE("Correctly adds rule")
    {
        stochastic::Vessel vessel;

        auto A = vessel.add("A", 0);
        auto B = vessel.add("B", 0);
        stochastic::ReactionRule rule{A >> 0.1 >>= B};

        auto& r = vessel.add(rule);
        CHECK(&r == &vessel.getRules().back());
    }
}