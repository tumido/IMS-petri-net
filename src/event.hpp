/**
 * @file event.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Event class which specifies calendar actions
 */
#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include <vector>
#include "transition.hpp"
#include "token.hpp"
#include "debug.hpp"
#include "stats.hpp"

class Event {
private:
    double time;
    double duration;
    Transition * transition;
public:
    Event(double , double, Transition * , std::vector<Token *> *);
    ~Event();
    double GetTime() const { return this->time; };
    double GetDuration() const { return this->duration; };
    Transition * GetTransitionPtr();
    void AddToken(Token *);
    std::vector<Token *> * Tokens;
    bool operator < (const Event& ref) const
    {
        return (this->time < ref.time);
    };
};

#endif // __EVENT_HPP__
