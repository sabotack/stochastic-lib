#include <ostream>
#include <reaction_rule.hpp>

/* RQ2: Provide pretty-printing of the reaction network in a) human readable format and b) network
 * graph (e.g. Fig. 4). */
std::ostream &stochastic::operator<<(std::ostream &os, const ReactionRule &rule)
{
    const auto &input = rule.input.reactants;
    for (size_t i = 0; i < input.size(); i++) {
        os << input[i].name;
        if (i != input.size() - 1) {
            os << " + ";
        }
    }

    os << " >> " << rule.rate << " >>= ";

    const auto &output = rule.output.reactants;
    for (size_t i = 0; i < output.size(); i++) {
        os << output[i].name;
        if (i != output.size() - 1) {
            os << " + ";
        }
    }
    return os;
}
