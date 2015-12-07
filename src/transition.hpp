/**
 * @file transition.hpp
 * @author Albert Uchytil
 * @brief Data structure for transition
 */
#ifndef __TRANSITION_HPP__
#define __TRANSITION_HPP__

#include "component.hpp"

#include <string>

enum class TimeType { Constant, Generated };

class Transition : public Component {
private:
public:
  Transition(std::string id) : Component(id) { };
  int Probability;
  int Priority;
  int Time;
};

#endif // __TRANSITION_HPP__
