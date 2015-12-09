/**
 * @file transition.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Data structure for transition
 */
#ifndef __TRANSITION_HPP__
#define __TRANSITION_HPP__

class Event;
class Connection;

#include "component.hpp"
#include "token.hpp"
#include "time_exp.hpp"

#include <string>

enum class TransType { TimeConstant, TimeGenerated, Priority, Probability };

class Transition : public Component {
private:
public:
  Transition(std::string id) : Component(id) { };
  int Value;
  TransType Type;
  bool IsFeasible();
  Event * CreateEvent(double simtime);
};

#endif // __TRANSITION_HPP__
