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
public:
  Place(std::string id) : Component(id) { };
};

#endif // __PLACE_HPP__
