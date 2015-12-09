/**
 * @file place.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Data structure for places
 */
#ifndef __PLACE_HPP__
#define __PLACE_HPP__

#include "component.hpp"

#include <string>

class Place : public Component {
private:
  int freespots;
public:
  Place(std::string id) : Component(id) { };
  void SetCapacity(int capacity);
  int GetFreeCount();
  int GetCount();
  bool isFree();
  void LeavePlace();
  bool EnterPlace();
  int Capacity = 1;
};

#endif // __PLACE_HPP__
