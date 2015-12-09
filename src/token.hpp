/**
 * @file token.hpp
 * @author Albert Uchytil
 * @brief Data structure for Tokens
 */
#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

class Place;

#include <cstddef>

class Token {
private:
    bool planned = false;
    int id;
public:
  Token(int id);
  Place *Location = NULL;
  void SetPlanned();
  bool isPlanned() { return planned; };
  int GetId() { return this->id; };
};

#endif // __TOKEN_HPP__
