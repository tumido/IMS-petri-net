/**
 * @file token.cpp
 * @author Albert Uchytil
 * @brief Data structure implementation for Tokens
 */

#include "token.hpp"

Token::Token(int id)
{
  this->id = id;
}

void Token::SetPlanned() {
    this->planned = true;
}

void Token::ClearPlanned() {
    this->planned = false;
}
