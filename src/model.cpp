/**
 * @file model.cpp
 * @author Albert Uchytil
 * @brief Implementation of model class for simulation
*/

#include "model.hpp"

bool Model::existsConnection(string id)
{
  return this->findConnection(id) != NULL;
}

Connection* Model::findConnection(string id)
{
  for (unsigned int i = 0; i < this->connections.size(); i++) {
    if (this->connections[i]->Id == id)
      return this->connections[i];
  }
  return NULL;
}

bool Model::existsPlace(string id)
{
  return this->findPlace(id) != NULL;
}

Place* Model::findPlace(string id)
{
  for (unsigned int i = 0; i < this->places.size(); i++) {
    if (this->places[i]->Id == id)
      return this->places[i];
  }
  return NULL;
}

bool Model::existsTransition(string id)
{
  return this->findTransition(id) != NULL;
}

Transition* Model::findTransition(string id)
{
  for (unsigned int i = 0; i < this->transitions.size(); i++) {
    if (this->transitions[i]->Id == id)
      return this->transitions[i];
  }
  return NULL;
}

void Model::AddConnection(string pId, string tId, ConnectionType type)
{
  auto place = this->findPlace(pId);
  auto trans = this->findTransition(tId);

  if (place != NULL && trans != NULL) {
    auto conn = new Connection("#yolo");
    conn->Tr = trans;
    conn->Pl = place;
    conn->Type = type;
    this->connections.push_back(conn);
  }
}

void Model::AddPlace(string id)
{
  this->AddPlace(id, 20);
}

void Model::AddPlace(string id, int capacity)
{
  if (!this->existsPlace(id)) {
    auto place = new Place(id);
    place->SetCapacity(capacity);
    this->places.push_back(place);
  }
}

void Model::AddToken(string id, string pId)
{
  auto place = this->findPlace(pId);
  if (place != NULL) {
    Token* token = new Token(id);
    if (token->Move(place))
      this->tokens.push_back(token);
    else
      delete token;
  }
}

void Model::AddTransition(string id, int prob, int priority, int timec, TransType type)
{
  if (!this->existsTransition(id)) {
    auto tran = new Transition(id);
    tran->Probability = prob;
    tran->Priority = priority;
    tran->Time = timec;
    tran->Type = type;
    this->transitions.push_back(tran);
  }
}
