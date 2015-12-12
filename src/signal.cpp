/**
 * @file signal.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SignalHandler
 */

#include "signal.hpp"

/**
 * Model to print stats.
 */
Model* SignalHandler::model = NULL;

/**
 * Handles received signals.
 */
void SignalHandler::handler(int signum)
{
  debug("SignalHandler", "signal handled");
  if (SignalHandler::model != NULL) {
    model->PrintStats();
    delete model;
  }
  exit(1);
}

/**
 * Sets up model to print when handling.
 *
 * @param model Model to watch
 */
void SignalHandler::SetupModel(Model *model)
{
  debug("SignalHandler", "setting up model for handling");
  SignalHandler::model = model;
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
