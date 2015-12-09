/**
 * @file connection.hpp
 * @author Albert Uchytil
 * @brief Data structure for connecting transitions and places
 */
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

class Transition;

#include "component.hpp"
#include "place.hpp"

enum class ConnectionType {FromPlace, ToPlace};

class Connection {
private:
public:
  Transition *Tr = NULL;
  Place *Pl = NULL;
  ConnectionType Type;
  int Capacity = 1;
};

#endif // __CONNECTION_HPP__
