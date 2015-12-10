/**
 * @file transition.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Data structure for transition
 */
#include "transition.hpp"

bool Transition::IsFeasible() {
    debug("transition", "checking feasibility for planning");
    std::vector<Connection*>::iterator conn_it;
    // there are enough tokens on input places
    for (conn_it = this->Inputs.begin(); conn_it != this->Inputs.end(); conn_it++) {
        if ((*conn_it)->Pl->GetCount() < (*conn_it)->Capacity)
            return false;
    }
    return true;
}

bool Transition::IsFeasibleNow() {
    debug("transition", "checking feasibility in time");
    std::vector<Connection*>::iterator conn_it;
    // there is enough capacity on output places
    for (conn_it = this->Outputs.begin(); conn_it != this->Outputs.end(); conn_it++) {
        if (! (*conn_it)->Pl->WillFit((*conn_it)->Capacity) )
            return false;
    }
    return true;
}

Place* Transition::Input()
{
  if (this->Inputs.size() == 0) {
    return NULL;
  } else {
    return this->Inputs[0]->Pl;
  }
}
