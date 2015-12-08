/**
 * @file model.cpp
 * @author Albert Uchytil
 * @brief Implementation of model class for simulation
*/

#include "model.hpp"

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
    auto conn = new Connection();
    conn->Tr = trans;
    conn->Pl = place;
    conn->Type = type;
    if (type == ConnectionType::FromPlace) {
      trans->Inputs.push_back(conn);
      place->Outputs.push_back(conn);
    } else {
      trans->Outputs.push_back(conn);
      place->Inputs.push_back(conn);
    }
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

void Model::AddTransition(string id, int prob)
{
  if (!this->existsTransition(id)) {
    auto tran = new Transition(id);
    tran->Value = prob;
    tran->Type = TransType::Probability;
    this->transitions.push_back(tran);
  }
}

void Model::AddTransitionP(string id, int priority)
{
  if (!this->existsTransition(id)) {
    auto tran = new Transition(id);
    tran->Value = priority;
    tran->Type = TransType::Priority;
    this->transitions.push_back(tran);
  }
}

void Model::AddTransition(string id, int timec, TransType type)
{
  if (!this->existsTransition(id)) {
    auto tran = new Transition(id);
    tran->Value = timec;
    tran->Type = type;
    this->transitions.push_back(tran);
  }
}
