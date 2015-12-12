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
#include "debug.hpp"

#include <string>
#include <sstream>

enum class TransType { TimeConstant, TimeGenerated, Priority, Probability };

class Transition : public Component {
private:
  unsigned int count = 0;
  double totalTime = 0;
public:
  Transition(std::string id) : Component(id) { };
  int Value;
  TransType Type;
  bool IsFeasible();
  bool IsFeasibleNow();
  Place* Input();
  unsigned int GetCount() { return count; };
  double GetAverageTime() { return totalTime / ((count > 0) ? count : 1); }
  void Apply(double timev);
  void PrintStatsPriority();
  void PrintStatsTimed();
};

#endif // __TRANSITION_HPP__
