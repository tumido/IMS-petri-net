/**
 * @file calendar.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Calendar of actions for simulation
 */
#ifndef __CALENDAR_HPP__
#define __CALENDAR_HPP__

#include <vector>
#include <set>
#include "event.hpp"
#include "stats.hpp"

struct compare {
    bool operator() (const Event * first, const Event * second) const {
        return first->GetTime() < second->GetTime();
    }
};

class Calendar {
private:
    int added;
    int proceed;
    int removed;
public:
    std::multiset<Event *, compare> List;
    Calendar();
    ~Calendar();
    void AppendEvent(Event *);
    Event * GetEvent();
    bool Empty();
    void IncRemoved() { this->removed++; };
    void IncProceed() { this->proceed++; };
    void PrintStats();
};

#endif // __CALENDAR_HPP__
