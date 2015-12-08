/**
 * @file model.hpp
 * @author Albert Uchytil
 * @brief Model class for simulation
 */
#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "connection.hpp"
#include "place.hpp"
#include "token.hpp"
#include "transition.hpp"

#include <vector>

using namespace std;

class Model {
private:
  vector<Connection*> connections;
  vector<Place*> places;
  vector<Token*> tokens;
  vector<Transition*> transitions;

  bool existsConnection(string id);
  Connection* findConnection(string id);
  bool existsPlace(string id);
  Place* findPlace(string id);
  bool existsTransition(string id);
  Transition* findTransition(string id);

public:
  void AddConnection(string pId, string tId, ConnectionType type);
  void AddPlace(string id);
  void AddPlace(string id, int capacity);
  void AddToken(string id, string pId);
  void AddTransition(string id, int prob);
  void AddTransitionP(string id, int priority);
  void AddTransition(string id, int time, TransType type);
  vector<Token*> GetTokens() { return this->tokens; };
};

#endif // __MODEL_HPP__
