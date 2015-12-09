/**
 * @file token.hpp
 * @author Albert Uchytil
 * @brief Data structure for Tokens
 */
#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

class Place;
#include "component.hpp"

class Token : public Component {
private:
    bool planned = false;
public:
  Token(std::string id) : Component(id) { };
  Place *Location = NULL;
  void SetPlanned();
  void ClearPlanned();
  bool isPlanned() { return planned; };
};

#endif // __TOKEN_HPP__
