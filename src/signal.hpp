/**
 * @file signal.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SignalHandler
 */
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "debug.hpp"
#include "model.hpp"

#include <iostream>
#include <signal.h>
#include <stdlib.h>

class SignalHandler {
private:
  static Model* model;
  static void handler(int signum);
public:
  static void SetupHandlers();
  static void SetupModel(Model *model);
};

#endif // SIGNAL_HPP
