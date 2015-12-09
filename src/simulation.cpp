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
    // randomize seed
    RandomizeSeed();

    // setup
    this->simtime = 0;

    // initial planning
    this->PlanEvents();

    // simulate
    while (!calendar->Empty() && (this->simtime < this->endtime)) {
        // get event from calendar and simulate the transition
        Event * e = calendar->GetEvent();
        this->simtime = e->GetTime();
        // take action and make the transition
        this->PerformEvent(e);
        // plan newly available events
        this->PlanEvents();
    }
}
void Simulation::SetEndtime(double t) {
    this->endtime = t;
}

void Simulation::PlanEvents() {
    // normal transitions (priority, timed)
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

    // probability transitions, grouped -> pick one based on the roll
    std::vector<ProbTrans*>::iterator probtrans_it;
    std::vector<ProbTrans*> probtrans = this->model->GetProbGroups();
    Transition * t;

    // get all transitions
    for(probtrans_it = probtrans.begin(); probtrans_it != probtrans.end(); probtrans_it++) {
        // roll the dice and pick transition within group
        t = (*probtrans_it)->PickTransition(RollPercentage());
        // if transition is feasible, plan it
        if (t->IsFeasible()) {
            event = this->CreateEvent(t);
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
        time = time + GenerateDelayExp(trans->Value);
    }
    Event * event = new Event(time, trans, tokens);
    return event;
}
void Simulation::PerformEvent(Event * event) {
    return;
}