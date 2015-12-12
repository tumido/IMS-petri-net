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
    //dtor, destruct tokens vector
    delete Tokens;
    debug("event", "destroyed");
}

/**
 * Return pointer to transition (transition is private)
 *
 * @return tranistion poiter
 */
Transition * Event::GetTransitionPtr() {
    return this->transition;
}

/**
 * Add token to event's evidence
 *
 * Push token pointer to the events vector containig all tokens affected by the
 * transition.
 * @param token Token that should be added
 */
void Event::AddToken(Token * token) {
    debug("event", "adding token");
    this->Tokens->push_back(token);
}
