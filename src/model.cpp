/**
 * @file model.cpp
 * @author Albert Uchytil
 * @brief Implementation of model class for simulation
*/

#include "model.hpp"

Model::~Model()
{
  for (unsigned int i = 0; i < this->connections.size(); i++)
    delete this->connections[i];

  for (unsigned int i = 0; i < this->places.size(); i++)
    delete this->places[i];

  for (unsigned int i = 0; i < this->tokens.size(); i++)
    delete this->tokens[i];

  for (unsigned int i = 0; i < this->transitions.size(); i++)
    delete this->transitions[i];

  for (unsigned int i = 0; i < this->probstranses.size(); i++)
    delete this->probstranses[i];
}

bool Model::existsPlace(string id)
{
  debug("model", "checks if place with id '" + id + "' exists");
  return this->findPlace(id) != NULL;
}

Place* Model::findPlace(string id)
{
  debug("model", "searches for place with id '" + id + "'");
  for (unsigned int i = 0; i < this->places.size(); i++) {
    if (this->places[i]->Id == id) {
      debug("model", "place found");
      return this->places[i];
    }
  }
  debug("model", "place not found");
  return NULL;
}

bool Model::existsTransition(string id)
{
  debug("model", "checks if transition with id '" + id + "' exists");
  return this->findTransition(id) != NULL;
}

Transition* Model::findTransition(string id)
{
  debug("model", "searches for transition with id '" + id + "'");
  for (unsigned int i = 0; i < this->transitions.size(); i++) {
    if (this->transitions[i]->Id == id) {
      debug("model", "transition found");
      return this->transitions[i];
    }
  }
  debug("model", "transition not found");
  return NULL;
}

void Model::AddConnection(string pId, string tId, ConnectionType type)
{
  debug("model", "connects '" + pId + "' with '" + tId + "'");
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
    debug("model", "added connection");
    this->connections.push_back(conn);
  } else {
    debug("model", "connection was not added");
  }
}

void Model::AddPlace(string id)
{
  debug("model", "added new place with unlimited capacity");
  this->AddPlace(id, 0);
}

void Model::AddPlace(string id, int capacity)
{
  debug("model", "added new place with capacity");
  if (!this->existsPlace(id)) {
    auto place = new Place(id);
    place->SetCapacity(capacity);
    this->places.push_back(place);
  }
}

void Model::AddTransition(string id)
{
  debug("model", "added new transitions");
  this->AddTransitionP(id, 0);
}

void Model::AddTransition(string id, int prob)
{
  if (!this->existsTransition(id)) {
    debug("model", "added new probability transition");
    auto tran = new Transition(id);
    tran->Value = prob;
    tran->Type = TransType::Probability;
    this->transitions.push_back(tran);
  } else {
    debug("model", "failed to add transition");
  }
}

void Model::AddTransitionP(string id, int priority)
{
  if (!this->existsTransition(id)) {
    debug("model", "added priority transition");
    auto tran = new Transition(id);
    tran->Value = priority;
    tran->Type = TransType::Priority;
    this->transitions.push_back(tran);
  } else {
    debug("model", "failed to add priority transition");
  }
}

void Model::AddTransition(string id, int timec, TransType type)
{
  if (!this->existsTransition(id)) {
    debug("model", "added time transition");
    auto tran = new Transition(id);
    tran->Value = timec;
    tran->Type = type;
    this->transitions.push_back(tran);
  } else {
    debug("model", "failed to add time transition");
  }
}

void Model::AddToken(string pId)
{
  auto place = this->findPlace(pId);
  if (place != NULL) {
    debug("model", "added token");
    place->AddToken(this->NewToken());
  } else {
    debug("model", "failed to add token");
  }
}

void Model::AddToken(string pId, unsigned int count)
{
  for (unsigned int i = 0; i < count; i++)
    this->AddToken(pId);
}

ProbTrans* Model::findProbTransSameEntrance(Transition *tr)
{
  debug("model", "searching for ProbTrans");
  ProbTrans* prtr = NULL;
  for (unsigned int i = 0; i < this->probstranses.size(); i++) {
    prtr = this->probstranses[i];
    if (prtr->Input == tr->Input()) {
      debug("model", "ProbTrans found");
      return prtr;
    }
  }
  debug("model", "ProbTrans not found");
  return prtr;
}

void Model::assignProbTrans(Transition *tr)
{
  auto prtr = this->findProbTransSameEntrance(tr);
  if (prtr != NULL) {
    debug("model", "assigning Transiton to ProbTrans");
    prtr->transitions.push_back(tr);
  } else {
    debug("model", "creating new ProbTrans");
    prtr = new ProbTrans();
    prtr->transitions.push_back(tr);
    prtr->Input = tr->Input();
    this->probstranses.push_back(prtr);
  }
}

void Model::splitTransitions()
{
  debug("model", "splitting transitions to different groups");
  Transition* tr;
  for (unsigned int i = 0; i < this->transitions.size(); i++) {
    tr = this->transitions[i];
    if (tr->Type == TransType::Probability) {
      debug("model", "probability transition found");
      this->assignProbTrans(tr);
    } else if (tr->Inputs.size() == 0) {
      if (tr->Type == TransType::TimeConstant || tr->Type == TransType::TimeGenerated) {
        debug("model", "generator found");
        this->generators.push_back(tr);
      }
    } else {
      debug("model", "regular transition found");
      this->normaltrans.push_back(tr);
    }
  }
}

bool Model::SetupAndValidate()
{
  debug("model", "setting up model");
  this->splitTransitions();
  return true;
}

Token* Model::NewToken()
{
  debug("model", "generating new token");
  Token* token = new Token(this->tokenId);
  this->tokenId++;
  this->tokens.push_back(token);
  return token;
}

void Model::RemoveToken(Token *token)
{
  debug("model", "removing token");
  tokens.erase(std::remove(tokens.begin(), tokens.end(), token));
}
