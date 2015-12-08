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
bool Token::Move(Place *newPlace)
{
  if (this->Location != NULL)
    this->Location->LeavePlace();
  if (newPlace->EnterPlace()) {
    this->Location = newPlace;
    return true;
  } else
    return false;
}
