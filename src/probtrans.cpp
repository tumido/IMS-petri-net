/**
 * @file probtrans.cpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Class consisting of probability transitions and their input
 */

#include "probtrans.hpp"

bool ProbTrans::isValid()
{
  auto sum = 0;
  for (unsigned int i = 0; i < this->transitions.size(); i++) {
    sum += this->transitions[i]->Value;
  }
  return sum == 100;
}
