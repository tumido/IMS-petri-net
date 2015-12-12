/**
 * @file signal.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SignalHandler
 */

#include "signal.hpp"

/**
 * Model to print stats.
 */
Simulation* SignalHandler::simulation = NULL;

/**
 * Handles received signals.
 */
void SignalHandler::handler(int signum)
{
  debug("SignalHandler", "signal handled");
  if (SignalHandler::simulation != NULL) {
    simulation->PrintStats();
    delete simulation;
  }
  exit(1);
}

/**
 * Sets up simulation to print when handling.
 *
 * @param simulation Model to watch
 */
void SignalHandler::SetupSim(Simulation *simulation)
{
  debug("SignalHandler", "setting up simulation for handling");
  SignalHandler::simulation = simulation;
}

/**
 * Sets up signal handling.
 */
void SignalHandler::SetupHandlers()
{
  debug("SignalHandler", "setting up signal handlers");
  if (signal((int)SIGTERM, SignalHandler::handler) == SIG_ERR ||
      signal((int)SIGQUIT, SignalHandler::handler) == SIG_ERR ||
      signal((int)SIGINT, SignalHandler::handler) == SIG_ERR)
    std::cerr << "Unable to register signal handlers" << std::endl;
}
