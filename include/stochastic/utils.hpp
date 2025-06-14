#ifndef UTILS_HPP
#define UTILS_HPP
#include <functional>
#include <iosfwd>

#include "vessel.hpp"

namespace stochastic {
    using StateObserver = std::function<void(double, const SymbolTable<std::string, int>&)>;

    void plotTimeSeries(const std::string& title, const std::string& fileName, const std::vector<double>& times, const std::unordered_map<std::string, std::vector<int>>& values);
    void printVesselState(const SymbolTable<std::string, int>& symbols);
    void exportToDot(std::ostream &os, const Vessel& vessel);
}

#endif //UTILS_HPP
