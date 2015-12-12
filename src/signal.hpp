/**
 * @file signal.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SignalHandler
 */
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "debug.hpp"
#include "simulation.hpp"

#include <iostream>
#include <signal.h>
#include <stdlib.h>

class SignalHandler {
private:
  static Simulation * simulation;
  static void handler(int signum);
public:
  static void SetupHandlers();
  static void SetupSim(Simulation * simulation);
};

#endif // SIGNAL_HPP
