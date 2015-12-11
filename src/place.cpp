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
  debug("place", "capacity set");
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
    int count = 0;
    std::vector<Token*>::iterator tok_it;
    for(tok_it = this->tokens.begin(); tok_it < this->tokens.end(); tok_it++) {
        if (! (*tok_it)->isPlanned())
            count = count + 1;
    }
    return count;
}

Token* Place::GetToken()
{
  debug("place", "getting token");
  std::vector<Token*>::iterator tok_it;
  for(tok_it = this->tokens.begin(); tok_it < this->tokens.end(); tok_it++) {
    debug("place", "iterating token");
    if (! (*tok_it)->isPlanned()) {
      return (*tok_it);
    }
  }
  debug("place", "no token available");
  return NULL;
}

bool Place::AddToken(Token *token)
{
  debug("place", "adding token");
  if (this->EnterPlace()) {
    this->tokens.push_back(token);
    token->Location = this;
    debug("place", "token added");
    return true;
  }
  return false;
}

void Place::RemoveToken(Token *token)
{
  debug("place", "removing token");
  tokens.erase(std::remove(tokens.begin(), tokens.end(), token));
  token->Location = NULL;
  std::cout << "tokens in place " << tokens.size() << std::endl;
}
