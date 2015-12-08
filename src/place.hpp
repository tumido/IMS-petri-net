/**
 * @file place.hpp
 * @author Albert Uchytil
 * @brief Data structure for places
 */
#ifndef __PLACE_HPP__
#define __PLACE_HPP__

#include "component.hpp"

class Place : public Component {
private:
  int freespots;
public:
  Place(std::string id) : Component(id) { };
  void SetCapacity(int capacity);
  int GetFreeCount();
  bool isFree();
  void LeavePlace();
  bool EnterPlace();
};

#endif // __PLACE_HPP__
