/**
 * @file event.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Event class which specifies calendar actions
 */
#include "event.hpp"

Event::Event(double t, Transition * trans, std::vector<Token *> * tok):
    time(t), transition(trans), Tokens(tok) {
    //ctor
}

Event::~Event() {
    //dtor
    delete Tokens;
    debug("event", "destroyed");
}

Transition * Event::GetTransitionPtr() {
    return this->transition;
}

void Event::AddToken(Token * token) {
    debug("event", "adding token");
    this->Tokens->push_back(token);
}
