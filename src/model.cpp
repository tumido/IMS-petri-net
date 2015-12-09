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

void Model::splitTransitions()
{
  Transition* tr;
  std::vector<int> used;
  for (unsigned int i = 0; i < this->transitions.size(); i++) {
    tr = this->transitions[i];
    if (tr->Type == TransType::Priority) {
      //if(std::find(v.begin(), v.end(), x) != v.end()) {

      //}
    } else if (tr->Inputs.size() == 0) {
      if (tr->Type == TransType::TimeConstant && tr->Type == TransType::TimeGenerated)
        this->generators.push_back(tr);
    } else {
      this->normaltrans.push_back(tr);
    }
  }
}

bool Model::SetupAndValidate()
{
  this->splitTransitions();
  return true;
}

Token* Model::NewToken()
{
  Token* token = new Token(this->tokenId);
  this->tokenId++;
  this->tokens.push_back(token);
  return token;
}

void Model::RemoveToken(Token *token)
{
  tokens.erase(std::remove(tokens.begin(), tokens.end(), token), tokens.end());
  delete token;
}
