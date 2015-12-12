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

/**
 * Run the simulation
 *
 * The core function of model simulation. Does the setup (inital planning of
 * events, generators planning). Then iterates through the calendar and one by
 * one process the events. After each event is proceed check if the rest of
 * planned events are still feasible. Then it plans the newly available events.
 * Iteration stops if the endtime is reached or the calendar is empty.
 */
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
        // print status
        cout << "\rCurrent simulation time = " << fixed << setprecision(5) <<this->simtime;
        //end simulation if endtime reached
        if (this->simtime >= this->endtime) {
            DeleteEvent(e);
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
    cout << "\n";
    debug("simulation", "done");
}

/**
 * Setting endtime
 *
 * Before the simulation run the endtime has to be set.
 * @param endtime double number that defines the end time of simulation
 */
void Simulation::SetEndtime(double t) {
    this->endtime = t;
}

/**
 * Plan events
 *
 * Looks for feasible transitions and transition groups (probability transitions).
 * Takes each transition and checks it's feasibility. Is so, creates event and
 * adds it to the calendar. The same it does for the probability transition. It
 * rolls for probability, picks right transition.
 */
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

/**
 * Planning of generators
 *
 * Generations are stored in separate vector in model. That's because generators
 * should be planned before the simulation starts for whole simulation run time.
 * For each generator it's creating events in the spacing defined by the
 * generator's attributes (type: whether constant time or exponential
 * distribution, value: time/mean) until the end time is reached. The setup
 * presumes the first token is generated after the first transition time not at
 * the start of simulation. It also plans one event more after the end time (this
 * is for the purposes of checking if endtime is reached during the simulation run)
 */
void Simulation::PlanGenerators() {
    debug("simulation", "planning generators");
    std::vector<Transition*>::iterator gen_it;
    std::vector<Transition*> gens = this->model->GetGenerators();
    Event* event;
    double time = this->simtime;
    std::vector<Token*> * tokens;
    double duration;

    // get each generator
    for(gen_it = gens.begin(); gen_it != gens.end(); gen_it++) {
        // from the beginning of the universe until apocalypse
        time = this->simtime;
        while (time < this->endtime) {
            // set time of event
            if ((*gen_it)->Type == TransType::TimeConstant)
                duration = (*gen_it)->Value;
            else
                duration = GenerateDelayExp((*gen_it)->Value);
            time = time + duration;
            // create and plan event
            tokens =  new std::vector<Token*>;
            event = new Event(time, duration, (*gen_it), tokens);
            this->calendar->AppendEvent(event);
        }
    }
    debug("simulation", "all generators planned, done");
}

/**
 * Event creation
 *
 * Needs a pointer to transition that should be proceed. Each transition has
 * input connections and these point to the places with tokens. These tokens are
 * added to newly created vector and set as planned. Time for the event is set to
 * current simulation time plus transition time (fixed or generated)
 * @param trans Transition pointer
 */
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
    double duration = 0;
    if (trans->Type == TransType::TimeConstant) {
        duration = trans->Value;
    }
    else if (trans->Type == TransType::TimeGenerated) {
        duration = GenerateDelayExp(trans->Value);
    }
    time = time + duration;
    Event * event = new Event(time, duration, trans, tokens);
    debug("simulator", "new event created");
    return event;
}

/**
 * Delete token
 *
 * The function pop's the token from model, place and destroys it.
 * @param t Tkoen that should be removed
 */
void Simulation::PopToken(Token * t) {
    debug("simulator", "removing token");
    this->model->RemoveToken(t);
    Place * p = t->Location;
    p->RemoveToken(t);
    delete t;
    debug("simulator", "removed token");
}

/**
 * Delete event
 *
 * Completely destroy event and it's properties (tokens)
 * @param event that should be destroyed
 */
void Simulation::DeleteEvent(Event * event) {
    std::vector<Token *>::iterator t;
    for (t = event->Tokens->begin(); t != event->Tokens->end(); t++) {
        PopToken(*t);
    }
    event->Tokens->clear();
    delete event;
}

/**
 * Perform event
 *
 * Processing the event. At first it checks if the transition is feasible at the
 * time it should be proceed. It increments the counter of processed events,
 * destroys all tokens on input places and adds new one to the output places
 * (the amount is based on the connection capacity)
 * @param event The event that should be proceed
 */
void Simulation::PerformEvent(Event * event) {
    std::ostringstream s;
    s << "[" << this->simtime << "] started processing event on transition: " << event->GetTransitionPtr()->Id;
    debug("simulator", s.str());
    //check again if the event can be performed
    //input tokens are already reservated, but the output places could not have enough capacity
    if (! event->GetTransitionPtr()->IsFeasibleNow()) {
        DeleteEvent(event);
        return;
    }
    // increment the proceed events counter
    this->calendar->IncProceed();
    event->GetTransitionPtr()->Apply(event->GetDuration());
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

/**
 * Discard event
 *
 * Remove the event from the calendar but instead of destroying the tokens it just
 * clears the "planned" flag no tokens, increments the counter of removed tokens
 * and deletes the event from memory.
 * @param event Event that should be discarded
 */
void Simulation::DiscardEvent(Event * event) {
    debug("simulator", "discarding event");
    std::vector<Token*>::iterator token_it;
    for (token_it = event->Tokens->begin(); token_it != event->Tokens->end(); token_it++)
        (*token_it)->ClearPlanned();
    this->calendar->RemoveEvent(event);
    delete event;
    this->calendar->IncRemoved();
    debug("simulator", "event discarded");
}

/**
 * Check events
 *
 * Performs a checkup if all events in calendar are still doable. If not it
 * discards them.
 */
void Simulation::CheckEvents() {
    debug("simulator", "checking planned events if doable");
    std::multiset<Event*, compare>::iterator event_it;
    for (event_it = this->calendar->List.begin(); event_it != this->calendar->List.end(); event_it++) {
        // dont check for generators planned long time ahead (generators have 0 inputs)
        if ((*event_it)->GetTransitionPtr()->Inputs.size() != 0 && !(*event_it)->GetTransitionPtr()->IsFeasibleNow()) {
            this->DiscardEvent(*event_it);
        }
    }
    debug("simulator", "check-up done");
}

/**
 * Print statistics
 *
 * For simulation these statistics are printed: simtime and endtime
 */
void Simulation::PrintStats() {
    Stats::PrintHeader("SIMULATION", "value");
    Stats::PrintRow("Model name", this->model->GetName());
    Stats::PrintRow("Simulation time", this->simtime);
    Stats::PrintRow("Simulation pre-set endtime", this->endtime);

    this->calendar->PrintStats();
    this->model->PrintStats();
}
