/**
 * @file transition.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Data structure for transition
 */
#include "transition.hpp"

bool Transition::IsFeasible() {
    std::vector<Connection*>::iterator in_iter;
    for (in_iter = this->Inputs.begin(); in_iter != this->Inputs.end(); in_iter++) {
        if ((*in_iter)->Pl->GetCount() < (*in_iter)->Capacity)
            return false;
    }
    return true;
}
