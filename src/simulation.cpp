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
    while (!calendar->Empty() && (this->simtime < this->endtine)) {
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
    std::vector<Token*>::iterator token;
    std::vector<Token*> tokens = this->model->GetTokens();

    std::vector<Connection*>::iterator out_iter;
    std::vector<Connection*> out;

    // get all tokens
    for(token = tokens.begin(); token != tokens.end(); token++) {

        // iterate through its available transitions
        out = token->Location->Outputs;
        for(out_iter = out.begin(); out_iter != out.end(); out_iter++) {

            if (out->Transition->IsFeasible()) {
                // naplanovat
            }
        }
    }
}
