/**
 * @file place.cpp
 * @author Albert Uchytil
 * @brief Data structure implementation for places
 */

#include "place.hpp"

#include "transition.hpp"

/**
 * Sets capacity of the place.
 */
void Place::SetCapacity(int capacity)
{
  this->Capacity = capacity;
  this->freespots = capacity;
  debug("place", "capacity set");
}

/**
 * Returns number of available spots.
 */
int Place::GetFreeCount()
{
  return this->freespots;
}

/**
 * Checks whether the place is free.
 */
bool Place::isFree()
{
  return this->isUnlimited() || this->freespots > 0;
}

/**
 * Checks whether place is valid depending on it's outputs
 */
bool Place::isValid()
{
  TransType prev_type;
  TransType curr_type;

  if (Outputs.size() > 0)
    prev_type = Outputs[0]->Tr->Type;

  for (unsigned int i = 1; i < Outputs.size(); i++) {
    curr_type = Outputs[i]->Tr->Type;
    if (prev_type != curr_type)
      return false;
  }
  return true;
}

/**
 * Checks if the place capacity is unlimited.
 */
bool Place::isUnlimited()
{
  return this->Capacity == 0;
}

/**
 * Checks if the place will take particular number of tokens.
 *
 * @param count Number to check
 */
bool Place::WillFit(int count)
{
  return this->isUnlimited() || this->freespots <= count;
}

/**
 * Increases number of available spots..
 */
void Place::LeavePlace()
{
  if (this->freespots < this->Capacity)
    this->freespots++;
}

/**
 * Decreases number of available spots.
 */
bool Place::EnterPlace()
{
  if (this->isFree()) {
    this->freespots--;
    return true;
  } else
    return false;
}

/**
 * Gets number of tokens that are not planned.
 */
int Place::GetCount() {
    int count = 0;
    std::vector<Token*>::iterator tok_it;
    for(tok_it = this->tokens.begin(); tok_it < this->tokens.end(); tok_it++) {
        if (! (*tok_it)->isPlanned())
            count = count + 1;
    }
    return count;
}

/**
 * Gets firsts token that is not planned.
 */
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

/**
 * Adds token to the place.
 *
 * @param token Token to be added
 */
bool Place::AddToken(Token *token)
{
  debug("place", "adding token");
  if (this->EnterPlace()) {
    this->tokens.push_back(token);
    token->Location = this;
    debug("place", "token added");
    this->visited++;
    this->max = max < tokens.size() ? tokens.size() : max;
    return true;
  }
  return false;
}

/**
 * Removes token from the place.
 *
 * @param token Token to be removed
 */
void Place::RemoveToken(Token *token)
{
  debug("place", "removing token");
  tokens.erase(std::remove(tokens.begin(), tokens.end(), token));
  token->Location = NULL;
  std::ostringstream s;
    this->min = min > tokens.size() ? tokens.size() : min;
  s << "tokens in place " << this->Id << ": " << tokens.size();
  debug("place", s.str());
}

/**
 * Print statistics
 *
 * Outputs statistical table containing values: number of created and left tokens
 */
void Place::PrintStats() {
    Stats::PrintRow(this->Id, this->visited, this->max, this->min, this->tokens.size());
}
