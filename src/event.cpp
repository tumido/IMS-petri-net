/**
 * @file event.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Event class which specifies calendar actions
 */
#include "event.hpp"

Event::Event(double t, Transition * trans): time(t), transition(trans) {
    //ctor
}

Event::~Event() {
    //dtor
}

Transition * Event::GetTransitionPtr() {
    return this->transition;
}

void Event::AddToken(Token * token) {
    this->tokens.push_back(token);
}

Token * Event::PopToken() {
    if(this->tokens.size() == 0)
        return NULL;

    Token * t = this->tokens.front();
    tokens.erase(this->tokens.begin());
    return t;
}
