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

struct compare {
    bool operator() (const Event * first, const Event * second) const {
        return first->GetTime() < second->GetTime();
    }
};

class Calendar {
private:
    std::multiset<Event *, compare> list;
public:
    Calendar();
    ~Calendar();
    void AppendEvent(Event *);
    Event * GetEvent();
    void RemoveEvent();
    bool Empty();
};

#endif // __CALENDAR_HPP__
