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
            event = (*trans_it)->CreateEvent(this->GetSimtime());
            this->calendar->AppendEvent(event);
        }
    }
}
