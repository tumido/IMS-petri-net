/**
 * @file simulation.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Class which takes care of the simulation
 */

#include "simulation.hpp"


Simulation::Simulation() {
    calendar = new Calendar();
    model = new Model();
}
Simulation::~Simulation() {
    delete calendar;
    delete model;
}
void Simulation::Start() {
    this->simtime = 0;
    //naplanovat
    while (!calendar->Empty() && (this->simtime < this->endtime)) {
        Event * e = calendar->GetEvent();
        this->simtime = e->GetTime();
        //provest
        //naplanovat
    }
}
void Simulation::SetEndtime(double t) {
    this->endtime = t;
}

void Simulation::PlanEvent() {
    std::vector<Transition*>::iterator trans_it;
    std::vector<Transition*> trans = this->model->GetTransitions();
    Event* event;

    // get all transitions
    for(trans_it = trans.begin(); trans_it != trans.end(); trans_it++) {
        // if transition is feasible, plan it
        if ((*trans_it)->IsFeasible()) {
            event = this->CreateEvent(*trans_it);
            this->calendar->AppendEvent(event);
        }
    }
}
Event * Simulation::CreateEvent(Transition * trans) {
    //reserve tokens
    std::vector<Connection*>::iterator conn_it;
    std::vector<Token*> tokens;
    Token * token;
    // for each input connection grab all tokens needed
    for (conn_it = trans->Inputs.begin(); conn_it != trans->Inputs.end(); conn_it++) {
        for (int i = 0; i < (*conn_it)->Capacity; i++) {
            token = (*conn_it)->Pl->GetToken();
            tokens.push_back(token);
            token->SetPlanned();
        }
    }

    //set time
    //default time is for instant transition TransType::Priority
    double time = this->simtime;
    if (trans->Type == TransType::TimeConstant) {
        time = time + trans->Value;
    }
    else if (trans->Type == TransType::TimeGenerated) {
        time = time + GenerateExponential(trans->Value);
    }
    Event * event = new Event(time, trans, tokens);
    return event;
}
