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
    debug("calendar", "event added");
}

Event * Calendar::GetEvent() {
    Event * e = *(this->List.begin());
    this->List.erase(this->List.begin());
    debug("calendar", "event removed");
    return e;
}

bool Calendar::Empty() {
    debug("calendar", "is empty");
    return this->List.empty();
}
