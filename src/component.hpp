/**
 * @file component.hpp
 * @author Albert Uchytil
 * @brief Abstract data structure for model components
 */
#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

class Connection;

#include <string>
#include <vector>

class Component {
public:
  Component(std::string Id);
  std::string Id;
  std::vector<Connection*> Inputs;
  std::vector<Connection*> Outputs;
};

#endif // __COMPONENT_HPP__
