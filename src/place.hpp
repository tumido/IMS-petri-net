/**
 * @file place.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Data structure for places
 */
#ifndef __PLACE_HPP__
#define __PLACE_HPP__

#include "component.hpp"
#include "place.hpp"
#include "token.hpp"
#include "debug.hpp"
#include "stats.hpp"

#include <algorithm>
#include <string>
#include <sstream>

#define MAX_CAPACITY 10000

class Place : public Component {
private:
  int freespots;
  unsigned int max = 0;
  unsigned int min = MAX_CAPACITY;
  int visited = 0;
  std::vector<Token*> tokens;
public:
  Place(std::string id) : Component(id) { };
  void SetCapacity(int capacity);
  int GetFreeCount();
  int GetCount();
  bool isFree();
  bool isValid();
  bool isUnlimited();
  bool WillFit(int);
  void LeavePlace();
  bool EnterPlace();
  int Capacity = MAX_CAPACITY;
  Token * GetToken();
  bool AddToken(Token *);
  void RemoveToken(Token *);
  int GetMax() { return this->max; };
  int GetMin() { return this->min; };
  int GetVisited() { return this-> visited; }
  void PrintStats();
};

#endif // __PLACE_HPP__
