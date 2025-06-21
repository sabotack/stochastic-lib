#ifndef EXAMPLES_HPP
#define EXAMPLES_HPP

#include <cmath>
#include "vessel.hpp"

namespace stochastic {
    inline Vessel abc(int a, int b, int c) {
        Vessel v{};
        const auto A = v.add("A", a);
        const auto B = v.add("B", b);
        const auto C = v.add("C", c);
        v.add(A + C >> 0.001 >>= B + C);
        return v;
    }

    inline Vessel circadianRhythm() {
        const auto alphaA = 50;
        const auto alpha_A = 500;
        const auto alphaR = 0.01;
        const auto alpha_R = 50;
        const auto betaA = 50;
        const auto betaR = 5;
        const auto gammaA = 1;
        const auto gammaR = 1;
        const auto gammaC = 2;
        const auto deltaA = 1;
        const auto deltaR = 0.2;
        const auto deltaMA = 10;
        const auto deltaMR = 0.5;
        const auto thetaA = 50;
        const auto thetaR = 100;
        auto v = stochastic::Vessel{};
        const auto env = v.add("env", 0, true);
        const auto DA = v.add("DA", 1);
        const auto D_A = v.add("D_A", 0);
        const auto DR = v.add("DR", 1);
        const auto D_R = v.add("D_R", 0);
        const auto MA = v.add("MA", 0);
        const auto MR = v.add("MR", 0);
        const auto A = v.add("A", 0);
        const auto R = v.add("R", 0);
        const auto C = v.add("C", 0);
        v.add((A + DA) >> gammaA >>= D_A);
        v.add(D_A >> thetaA >>= DA + A);
        v.add((A + DR) >> gammaR >>= D_R);
        v.add(D_R >> thetaR >>= DR + A);
        v.add(D_A >> alpha_A >>= MA + D_A);
        v.add(DA >> alphaA >>= MA + DA);
        v.add(D_R >> alpha_R >>= MR + D_R);
        v.add(DR >> alphaR >>= MR + DR);
        v.add(MA >> betaA >>= MA + A);
        v.add(MR >> betaR >>= MR + R);
        v.add((A + R) >> gammaC >>= C);
        v.add(C >> deltaA >>= R);
        v.add(A >> deltaA >>= env);
        v.add(R >> deltaR >>= env);
        v.add(MA >> deltaMA >>= env);
        v.add(MR >> deltaMR >>= env);
        return v;
    }

    inline Vessel seihr(uint32_t N) {
        auto v = Vessel{};
        const auto eps = 0.0009;
        const auto I0 = static_cast<size_t>(std::round(eps * N));
        const auto E0 = static_cast<size_t>(std::round(eps * N * 15));
        const auto S0 = N - I0 - E0;
        const auto R0 = 2.4;
        const auto alpha = 1.0 / 5.1;
        const auto gamma = 1.0 / 3.1;
        const auto beta = R0 * gamma;
        const auto P_H = 0.9e-3;
        const auto kappa = gamma * P_H * (1.0 - P_H);
        const auto tau = 1.0 / 10.12;
        const auto S = v.add("S", S0);
        const auto E = v.add("E", E0);
        const auto I = v.add("I", I0);
        const auto H = v.add("H", 0);
        const auto R = v.add("R", 0);
        v.add((S + I) >> beta / N >>= E + I);
        v.add(E >> alpha >>= I);
        v.add(I >> gamma >>= R);
        v.add(I >> kappa >>= H);
        v.add(H >> tau >>= R);
        return v;
    }
}

#endif //EXAMPLES_HPP
