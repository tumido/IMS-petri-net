/**
 * @file place.cpp
 * @author Albert Uchytil
 * @brief Data structure implementation for places
 */

#include "place.hpp"

void Place::SetCapacity(int capacity)
{
  this->Capacity = capacity;
  this->freespots = capacity;
}

int Place::GetFreeCount()
{
  return this->freespots;
}

bool Place::isFree()
{
  return this->isUnlimited() || this->freespots > 0;
}

bool Place::isUnlimited()
{
  return this->Capacity == 0;
}

bool Place::WillFit(int count)
{
  return this->isUnlimited() || this->freespots <= count;
}

void Place::LeavePlace()
{
  if (this->freespots < this->Capacity)
    this->freespots++;
}

bool Place::EnterPlace()
{
  if (this->isFree()) {
    this->freespots--;
    return true;
  } else
    return false;
}

int Place::GetCount() {
    return this->Capacity - this->freespots;
}

Token* Place::GetToken()
{
  Token *token;
  for(unsigned int i = 0; i < this->tokens.size(); i++) {
    token = this->tokens[i];
    if (token->isPlanned()) {
      return token;
    }
  }
  return NULL;
}

bool Place::AddToken(Token *token)
{
  if (this->EnterPlace()) {
    this->tokens.push_back(token);
    token->Location = this;
  }
  return false;
}

void Place::RemoveToken(Token *token)
{
  tokens.erase(std::remove(tokens.begin(), tokens.end(), token));
  token->Location = NULL;
}
