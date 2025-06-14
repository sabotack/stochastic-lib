#include <fstream>
#include <iostream>

#include "examples.hpp"
#include "stochastic_lib.hpp"

int main() {
    std::cout << __cplusplus << std::endl;

    const auto seihr = stochastic::seihr(10000);
    // std::ofstream file("testing_covidd.dot");
    // stochastic::export_to_dot(file, seihr);

    for (auto& rule : seihr.getRules()) {
        std::cout << rule << "\n";
    }

    //
    // const auto abc = stochastic::abc(100, 0, 1);
    // auto s = stochastic::Simulator{abc};
    //
    // // s.simulate(2000);
    //
    // const stochastic::Reactant A("A", 2);
    // const stochastic::Reactant B("B", 3);
    // const stochastic::Reactant C("C", 4);
    // const stochastic::Reactant D("D", 5);
    //
    //
    // auto r1 = A + B >> 50.0 >>= D + C;
    // auto r2 = C + D >> 2 >>= A;

    return 0;
}
