/**
 * @file transition.hpp
 * @author Albert Uchytil
 * @brief Data structure for transition
 */
#include "transition.hpp"

bool Transition::IsFeasible() {
    std::vector<Connection*>::iterator in_iter;
    for (in_iter = this->Inputs.begin(); in_iter != this->Inputs.end(); in_iter++) {
        // rozhodnout
    }
    return true;
}
