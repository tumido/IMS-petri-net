/**
 * @file token.hpp
 * @author Albert Uchytil
 * @brief Data structure for Tokens
 */
#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

class Place;

#include "debug.hpp"
#include <cstddef>

class Token {
private:
    bool planned = false;
    int id;
public:
  Token(int i): id(i) {};
  Place *Location = NULL;
  void SetPlanned() { this->planned = true; };
  void ClearPlanned() { this->planned = true; };
  bool isPlanned() { return planned; };
  int GetId() { return this->id; };
};

#endif // __TOKEN_HPP__
