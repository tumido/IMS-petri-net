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
    std::multiset<Event *, compare>::iterator i;

    for(i = List.begin(); i != List.end(); i++) {
        delete *i;
    }
    List.clear();
}

void Calendar::AppendEvent(Event * e) {
    this->List.insert(e);
}

Event * Calendar::GetEvent() {
    Event * e = *(this->List.begin());
    this->List.erase(this->List.begin());
    return e;
}

bool Calendar::Empty() {
    return this->List.empty();
}
