/**
 * @file probtrans.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Class consisting of probability transitions and their input
 */
#ifndef __PROBTRANS_HPP__
#define __PROBTRANS_HPP__

#include "place.hpp"
#include "transition.hpp"
#include "token.cpp"

#include <vector>

class ProbTrans {
private:
public:
  Place *Input;
  std::vector<Transition*> transitions;
  bool isValid();
  Transition* PickTransition(int);
};

#endif // __PROBTRANS_HPP__
