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
  return this->freespots > 0;
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
