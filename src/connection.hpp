/**
 * @file connection.hpp
 * @author Albert Uchytil
 * @brief Data structure for connecting transitions and places
 */
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include "component.hpp"
#include "place.hpp"
#include "transition.hpp"

#include <vector>

enum class ConnectionType {FromPlace, ToPlace};

class Connection {
private:
public:
  Transition *Tr = NULL;
  Place *Pl = NULL;
  ConnectionType Type;
  std::vector<Connection*> Inputs;
  std::vector<Connection*> Outputs;
};

#endif // __CONNECTION_HPP__
