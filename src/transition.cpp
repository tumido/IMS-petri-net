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

Event * Transition::CreateEvent(double simtime) {
    //reserve tokens
    std::vector<Connection*>::iterator conn_it;
    std::vector<Token*> tokens;
    Token * token;
    // for each input connection grab all tokens needed
    for (conn_it = this->Inputs.begin(); conn_it != this->Inputs.end(); conn_it++) {
        for (int i = 0; i < (*conn_it)->Capacity; i++) {
            token = (*conn_it)->Pl->GetToken()
            tokens.pushBack(token);
            token->SetPlanned();
        }
    }

    //set time
    //default time is for instant transition TransType::Priority
    double time = simtime;
    if (this->Type == TransType::TimeConstant) {
        time = time + this->Value;
    }
    else if (this->Type == TransType::TimeGenerated) {
        time = time + GenerateExponential(this->Value);
    }
    Event * event = new Event(time, this, tokens);
    return event;
}
