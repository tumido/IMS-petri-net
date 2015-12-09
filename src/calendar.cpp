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

    for(i = list.begin(); i != list.end(); i++) {
        delete *i;
    }
    list.clear();
}

void Calendar::AppendEvent(Event * e) {
    this->list.insert(e);
}

Event * Calendar::GetEvent() {
    return * (this->list.begin());
}

void Calendar::RemoveEvent() {
    Event * e = * (this->list.begin());
    delete e;
    this->list.erase(this->list.begin());
}

bool Calendar::Empty() {
    return this->list.empty();
}
