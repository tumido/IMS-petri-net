/**
 * @file simulation.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Class which takes care of the simulation
 */

#include "simulation.hpp"


Simulation::Simulation(Model *m): model(m) {
    calendar = new Calendar();
}
Simulation::~Simulation() {
    delete calendar;
    delete model;
}
void Simulation::Start() {
    debug("simulation", "starting");
    // randomize seed
    RandomizeSeed();

    // setup
    this->simtime = 0;

    // initial planning
    this->PlanGenerators();
    this->PlanEvents();

    // simulate
    while (!calendar->Empty()) {
        // get event from calendar and simulate the transition
        Event * e = calendar->GetEvent();
        this->simtime = e->GetTime();
        //end simulation if endtime reached
        if (this->simtime >= this->endtime) {
            debug("simulation", "endtime reached");
            break;
        }
        // take action and make the transition
        this->PerformEvent(e);
        // check if events are feasible
        this->CheckEvents();
        // plan newly available events
        this->PlanEvents();
    }
    debug("simulation", "done");
}
void Simulation::SetEndtime(double t) {
    this->endtime = t;
}

void Simulation::PlanEvents() {
    debug("simulation", "planning events");
    // normal transitions (priority, timed)
    std::vector<Transition*>::iterator trans_it;
    std::vector<Transition*> trans = this->model->GetTransitions();
    Event* event;

    // get all transitions
    for(trans_it = trans.begin(); trans_it != trans.end(); trans_it++) {
        // if transition is feasible, plan it
        if ((*trans_it)->IsFeasible() && (*trans_it)->IsFeasibleNow()) {
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
    debug("simulation", "all events planned, done");
}

void Simulation::PlanGenerators() {
    debug("simulation", "planning generators");
    std::vector<Transition*>::iterator gen_it;
    std::vector<Transition*> gens = this->model->GetGenerators();
    Event* event;
    double time = this->simtime;

    // get each generator
    for(gen_it = gens.begin(); gen_it != gens.end(); gen_it++) {
        // from the beginning of the universe until apocalypse
        time = this->simtime;
        while (time < this->endtime) {
            // set time of event
            if ((*gen_it)->Type == TransType::TimeConstant)
                time = time + (*gen_it)->Value;
            else
                time = time + GenerateDelayExp((*gen_it)->Value);
            // create and plan event
            event = new Event(time, (*gen_it), new std::vector<Token*>);
            this->calendar->AppendEvent(event);
        }
    }
    debug("simulation", "all generators planned, done");
}

Event * Simulation::CreateEvent(Transition * trans) {
    debug("simulator", "creating new event");
    //reserve tokens
    std::vector<Connection*>::iterator conn_it;
    std::vector<Token*> * tokens = new std::vector<Token*>;
    Token * token;
    // for each input connection grab all tokens needed
    for (conn_it = trans->Inputs.begin(); conn_it != trans->Inputs.end(); conn_it++) {
        for (int i = 0; i < (*conn_it)->Capacity; i++) {
            token = (*conn_it)->Pl->GetToken();
            tokens->push_back(token);
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
    debug("simulator", "new event created");
    return event;
}

void Simulation::PopToken(Token * t) {
    debug("simulator", "removing token");
    this->model->RemoveToken(t);
    Place * p = t->Location;
    p->RemoveToken(t);
    debug("simulator", "removed token");
}


void Simulation::PerformEvent(Event * event) {
    std::ostringstream s;
    s << "[" << this->simtime << "] started processing event on transition: " << event->GetTransitionPtr()->Id;
    debug("simulator", s.str());
    //check again if the event can be performed
    //input tokens are already reservated, but the output places could not have enough capacity
    if (! event->GetTransitionPtr()->IsFeasibleNow()) {
        this->DiscardEvent(event);
        return;
    }

    // remove tokens from model and places
    std::vector<Token*>::iterator token_it;
    for (token_it = event->Tokens->begin(); token_it != event->Tokens->end(); token_it++) {
        PopToken(*token_it);
    }
    // create new tokens and add them to outputs of the transition
    std::vector<Connection*>::iterator conn_it;
    Token * token;
    for (conn_it = event->GetTransitionPtr()->Outputs.begin(); conn_it != event->GetTransitionPtr()->Outputs.end(); conn_it++) {
        for (int i = 0; i < (*conn_it)->Capacity; i++) {
            token = model->NewToken();
            (*conn_it)->Pl->AddToken(token);
        }
    }
    // destroy event
    delete event;
    debug("simulator", "event proceed");
}

void Simulation::DiscardEvent(Event * event) {
    debug("simulator", "discarding event");
    std::vector<Token*>::iterator token_it;
    for (token_it = event->Tokens->begin(); token_it != event->Tokens->end(); token_it++)
        (*token_it)->ClearPlanned();
    delete event;
    debug("simulator", "event discarded");
}

void Simulation::CheckEvents() {
    debug("simulator", "checking planned events if doable");
    std::multiset<Event*, compare>::iterator event_it;
    for (event_it = this->calendar->List.begin(); event_it != this->calendar->List.end(); event_it++) {
        if (! (*event_it)->GetTransitionPtr()->IsFeasibleNow())
            this->DiscardEvent(*event_it);
    }
    debug("simulator", "check-up done");
}
