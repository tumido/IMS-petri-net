/**
 * @file main.cpp
 * @author Albert Uchytil
 * @brief Entry point
 */

#include <iostream>
#include "test.hpp"
#include "model.hpp"
#include "simulation.hpp"
#include "debug.hpp"
#define YOLO 6

using namespace std;

int main(int argc, char* argv[])
{
  debug("main", "creating model");
  //Model * model = test::Model01();
  Model * model = test::Model02();
  debug("main", "validating model");
  model->SetupAndValidate();

  debug("main", "preparing simulation");
  Simulation * simulation =  new Simulation(model);
  simulation->SetEndtime(YOLO);

  cout << "Running simulation..." << endl;
  simulation->Start();
  cout << "*Done*" << endl;
}
