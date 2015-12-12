/**
 * @file probtrans.cpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Class consisting of probability transitions and their input
 */

#include "probtrans.hpp"

/**
 * Check if the structure is valid.
 */
bool ProbTrans::isValid()
{
  auto sum = 0;
  for (unsigned int i = 0; i < this->transitions.size(); i++) {
    sum += this->transitions[i]->Value;
  }
  return sum == 100;
}

/**
 * Chooses one of the transition.
 *
 * @param roll Value to pick a transition.
 */
Transition* ProbTrans::PickTransition(int roll)
{
  debug("probtrans", "picking transition");
  int current = 0;
  Transition* tr;
  for (unsigned int i = 0; i < this->transitions.size(); i++) {
    tr = this->transitions[i];
    current += tr->Value;
    if (roll < current) {
      debug("probtrans", "transition picked");
      return tr;
    }
  }
  debug("probtrans", "transition picked");
  return tr;
}

/**
 * Gets sum of all tokens that went throught
 */
unsigned int ProbTrans::GetSum()
{
  unsigned int sum = 0;
  for (unsigned int i = 0; i < transitions.size(); i++) {
    sum += transitions[i]->GetCount();
  }
  return sum;
}

void ProbTrans::PrintStats(unsigned int group)
{
  auto count = GetSum();
  for (unsigned int i = 0; i < transitions.size(); i++)
    transitions[i]->PrintStatsProbability(group, count);
}
