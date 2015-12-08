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

class Event {
private:
    double time;
    Transition * transition;
    std::vector<Token *> tokens;
public:
    Event(double , Transition * );
    ~Event();
    double GetTime() const { return this->time; };
    Transition * GetTransitionPtr();
    void AddToken(Token *);
    Token * PopToken();
    bool operator < (const Event& ref) const
    {
        return (this->time < ref.time);
    }
};

#endif // __EVENT_HPP__
