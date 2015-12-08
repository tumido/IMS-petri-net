/**
 * @file transition.hpp
 * @author Albert Uchytil
 * @brief Data structure for transition
 */
#ifndef __TRANSITION_HPP__
#define __TRANSITION_HPP__

#include "component.hpp"

#include <string>

enum class TransType { TimeConstant, TimeGenerated, Priority, Probability };

class Transition : public Component {
private:
public:
  Transition(std::string id) : Component(id) { };
  int Value;
  TransType Type;
  bool IsFeasible();
};

#endif // __TRANSITION_HPP__
