/**
 * @file token.hpp
 * @author Albert Uchytil
 * @brief Data structure for Tokens
 */
#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include "component.hpp"
#include "place.hpp"

class Token : public Component {
private:
public:
  Token(std::string id) : Component(id) { };
  Place *Location = NULL;
  bool Move(Place *newPlace);
};

#endif // __TOKEN_HPP__
