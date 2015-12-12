/**
 * @file component.cpp
 * @author Albert Uchytil
 * @brief Abstract data structure for model components
 */

#include "component.hpp"

/**
 * Component constructor
 */
Component::Component(std::string id)
{
  this->Id = id;
}
