/**
 * @file transition.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Data structure for transition
 */
#ifndef __TRANSITION_HPP__
#define __TRANSITION_HPP__


#include "component.hpp"
#include "token.hpp"
#include "rand_gen.hpp"
#include "connection.hpp"

#include <string>

enum class TransType { TimeConstant, TimeGenerated, Priority, Probability };

class Transition : public Component {
private:
public:
  Transition(std::string id) : Component(id) { };
  int Value;
  TransType Type;
  bool IsFeasible();
  bool IsFeasibleNow();
  Place* Input();
};

#endif // __TRANSITION_HPP__
