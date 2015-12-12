/**
 * @file calendar.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Calendar of actions for simulation
 */
#include "calendar.hpp"

Calendar::Calendar() {
    //ctor
    this->added = 0;
    this->proceed = 0;
    this->removed = 0;
}

Calendar::~Calendar() {
    //dtor, clean up left events
    debug("calendar", "destroying");
    std::multiset<Event *, compare>::iterator i;

    for(i = List.begin(); i != List.end(); i++) {
        delete *i;
    }
    List.clear();
    debug("calendar", "destroyed");
}

/**
 * Append event to calendar
 *
 * Func appends event to calendar's multiset (sorted by time) and increments
 * statistics counter
 * @param event Pointer to event that should be added to calendar
 */
void Calendar::AppendEvent(Event * e) {
    this->List.insert(e);
    this->added++;
    debug("calendar", "event added");
}

/**
 * Get event from calendar
 *
 * Pop event from calendar (remove it from multiset) and inc counter
 * @return event Event that has been popped from the calendar
 */
Event * Calendar::GetEvent() {
    Event * e = *(this->List.begin());
    this->List.erase(this->List.begin());
    this->proceed++;
    debug("calendar", "event pop");
    return e;
}

/**
 * Check if calendar is empty
 *
 * @return the status of calendar
 */
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

/**
 * Remove event
 *
 * Same as GetEvent() but does not return the counter and leave the counter as is
 * @param event Event that should be erased
 */
void Calendar::RemoveEvent(Event * event) {
    debug("calendar", 'removing event');
    this->List.erase(List.find(event));
}

/**
 * Print statistics
 *
 * Outputs statistical table containing values: added, removed and proceed count
 */
void Calendar::PrintStats() {
    Stats::PrintHeader("CALENDAR", "amount");
    Stats::PrintRow("Total events added", this->added);
    Stats::PrintRow("Total events proceed", this->proceed);
    Stats::PrintRow("Events removed while checkup", this->removed);
}
