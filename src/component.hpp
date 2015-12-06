/**
 * @file component.hpp
 * @author Albert Uchytil
 * @brief Abstract data structure for model components
 */
#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include <string>

class Component {
public:
  std::string Id;
  int Capacity = 1;
};

#endif // __COMPONENT_HPP__
