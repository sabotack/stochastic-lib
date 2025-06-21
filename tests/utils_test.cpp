#include "utils.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include "doctest/doctest.h"
#include "examples.hpp"

TEST_SUITE("stochastic::plotTimeSeries")
{
    TEST_CASE("Generates plot on valid input")
    {
        std::vector times = {0.0, 1.0, 2.0, 3.0};
        std::unordered_map<std::string, std::vector<int>> values = {
            {"A", {1, 2, 3, 4}},
            {"B", {4, 3, 2, 1}}
        };

        std::string title = "Test Plot";
        std::string fileName = "test_plot.png";

        std::filesystem::remove(fileName);

        CHECK_NOTHROW(stochastic::plotTimeSeries(title, fileName, times, values));
        CHECK(std::filesystem::exists(fileName));

        std::filesystem::remove(fileName);
    }

    TEST_CASE("Throws error on mismatched lengths")
    {
        std::vector times{0.0, 1.0, 2.0};
        std::unordered_map<std::string, std::vector<int>> values{
            {"A", {1, 2}}, // wrong length
        };

        CHECK_THROWS_AS(
            stochastic::plotTimeSeries("Mismatch", "fail.png", times, values),
            std::invalid_argument);
    }

    TEST_CASE("Throws error on empty input")
    {
        std::vector<double> times;
        std::unordered_map<std::string, std::vector<int>> values;

        CHECK_THROWS_AS(
            stochastic::plotTimeSeries("Empty", "empty.png", times, values), std::invalid_argument);
    }
}

TEST_SUITE("stochastic::exportToDot")
{
    TEST_CASE("Generates correct dot output")
    {
        auto v = stochastic::abc(1, 2, 3);

        std::ostringstream oss;
        CHECK_NOTHROW(stochastic::exportToDot(oss, v));

        std::string output = oss.str();

        CHECK(output.find("digraph {") != std::string::npos);
        CHECK(output.find("A [label=\"A\"") != std::string::npos);
        CHECK(output.find("B [label=\"B\"") != std::string::npos);
        CHECK(output.find("C [label=\"C\"") != std::string::npos);
        CHECK(output.find("A -> r0;") != std::string::npos);
        CHECK(output.find("C -> r0;") != std::string::npos);
        CHECK(output.find("r0 -> B;") != std::string::npos);
        CHECK(output.find("r0 -> C;") != std::string::npos);
        CHECK(output.find("r0 [label=\"0.001\"") != std::string::npos);
        CHECK(output.find('}') != std::string::npos);
    }
}
