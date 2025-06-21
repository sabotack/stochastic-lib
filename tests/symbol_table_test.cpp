#include "symbol_table.hpp"

#include "doctest/doctest.h"

TEST_SUITE("SymbolTable::add")
{
    TEST_CASE("Inserts key-value pair")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("A", 42, false);

        CHECK(table.contains("A"));
        CHECK(table.get("A") == 42);
    }

    TEST_CASE("Inserts internal symbol")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("X", 99, true);

        CHECK(table.contains("X"));
        CHECK(table.get("X") == 99);
        CHECK(table.isInternal("X"));
    }

    TEST_CASE("Throws error on duplicate key")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("A", 10, false);

        CHECK_THROWS_WITH(table.add("A", 20, false), "Key already exists: 'A'");
    }
}

TEST_SUITE("SymbolTable::getKeys")
{
    TEST_CASE("Returns all keys by default")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("A", 1, false);
        table.add("B", 2, true);
        table.add("C", 3, false);

        auto keys = table.getKeys();
        CHECK(keys.size() == 3);
        CHECK(std::find(keys.begin(), keys.end(), "A") != keys.end());
        CHECK(std::find(keys.begin(), keys.end(), "B") != keys.end());
        CHECK(std::find(keys.begin(), keys.end(), "C") != keys.end());
    }

    TEST_CASE("Excludes internals when requested")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("X", 10, true);
        table.add("Y", 20, false);

        auto keys = table.getKeys(true);
        CHECK(keys.size() == 1);
        CHECK(keys.front() == "Y");
    }
}

TEST_SUITE("SymbolTable::get")
{
    TEST_CASE("Returns value by reference")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("A", 42, false);

        int& val = table.get("A");
        CHECK(val == 42);

        val = 100;
        CHECK(table.get("A") == 100);
    }

    TEST_CASE("Throws error if key is not found")
    {
        stochastic::SymbolTable<std::string, int> table;

        CHECK_THROWS_WITH_AS(table.get("A"), "Key not found: 'A'", std::runtime_error);
    }

    TEST_CASE("Const overload works")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("A", 5, false);

        const auto& constTable = table;
        const int& val = constTable.get("A");
        CHECK(val == 5);
    }
}

TEST_SUITE("SymbolTable::contains")
{
    TEST_CASE("Returns true for existing key")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("X", 10, false);

        CHECK(table.contains("X"));
    }

    TEST_CASE("Returns false for missing key")
    {
        stochastic::SymbolTable<std::string, int> table;
        CHECK_FALSE(table.contains("A"));
    }
}

TEST_SUITE("SymbolTable::isInternal")
{
    TEST_CASE("Returns true for internal symbol")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("A", 1, true);

        CHECK(table.isInternal("A"));
    }

    TEST_CASE("Returns false for non-internal symbol")
    {
        stochastic::SymbolTable<std::string, int> table;
        table.add("A", 2, false);

        CHECK_FALSE(table.isInternal("A"));
    }

    TEST_CASE("Returns false for unknown key")
    {
        stochastic::SymbolTable<std::string, int> table;

        CHECK_FALSE(table.isInternal("A"));
    }
}