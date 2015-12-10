/**
 * @file model.hpp
 * @author Albert Uchytil
 * @brief Model class for simulation
 */
#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "connection.hpp"
#include "place.hpp"
#include "probtrans.hpp"
#include "token.hpp"
#include "transition.hpp"

#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;

class Model {
private:
  std::vector<Connection*> connections;
  std::vector<Place*> places;
  std::vector<Token*> tokens;
  std::vector<Transition*> transitions;
  std::vector<Transition*> normaltrans;
  std::vector<Transition*> generators;
  std::vector<ProbTrans*> probstranses;
  int tokenId = 0;

  bool existsConnection(string id);
  Connection* findConnection(string id);
  bool existsPlace(string id);
  Place* findPlace(string id);
  bool existsTransition(string id);
  Transition* findTransition(string id);
  void splitTransitions();

public:
  void AddConnection(string pId, string tId, ConnectionType type);
  void AddPlace(string id);
  void AddPlace(string id, int capacity);
  void AddToken(string pId);
  void AddTransition(string id, int prob);
  void AddTransitionP(string id, int priority);
  void AddTransition(string id, int time, TransType type);
  bool SetupAndValidate();
  std::vector<Token*> GetTokens() { return this->tokens; };
  std::vector<Transition*> GetTransitions() { return this->normaltrans; };
  std::vector<ProbTrans*> GetProbGroups() { return this->probstranses; };
  std::vector<Transition*> GetGenerators() { return this->generators; };
  Token* NewToken();
  void RemoveToken(Token *token);
};

#endif // __MODEL_HPP__
