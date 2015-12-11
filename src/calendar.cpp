/**
 * @file calendar.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Calendar of actions for simulation
 */
#include "calendar.hpp"

Calendar::Calendar() {
    //ctor
}

Calendar::~Calendar() {
    //dtor
    debug("calendar", "destroying");
    std::multiset<Event *, compare>::iterator i;

    for(i = List.begin(); i != List.end(); i++) {
        delete *i;
    }
    List.clear();
    debug("calendar", "destroyed");
}

void Calendar::AppendEvent(Event * e) {
    this->List.insert(e);
    this->added++;
    debug("calendar", "event added");
}

Event * Calendar::GetEvent() {
    Event * e = *(this->List.begin());
    this->List.erase(this->List.begin());
    this->proceed++;
    debug("calendar", "event pop");
    return e;
}

bool Calendar::Empty() {
    if (this->List.empty()) {
        debug("calendar", "is empty");
        return true;
    }
    else {
        debug("calendar", "full of events");
        return false;
    }
}

void Calendar::PrintStats() {
    Stats::PrintHeader("CALENDAR", "value");
    Stats::PrintRow("Total events added", this->added);
    Stats::PrintRow("Total events proceed", this->proceed);
    Stats::PrintRow("Events removed ()", this->removed);
}
