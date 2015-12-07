/**
 * @file token.cpp
 * @author Albert Uchytil
 * @brief Data structure implementation for Tokens
 */

#include "token.hpp"

/**
 * Moves token to different place
 *
 * @param newPlace New destination of token
 */
void Token::Move(Place *newPlace)
{
  this->Location = newPlace;
}
