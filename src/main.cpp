/**
 * @file main.cpp
 * @author Albert Uchytil
 * @brief Entry point
 */

#include <iostream>
#include <sstream>
#include "test.hpp"
#include "model.hpp"
#include "simulation.hpp"
#include "debug.hpp"
#define YOLO 1000

using namespace std;

int main(int argc, char* argv[])
{
  debug("main", "creating model");
  Model * model;
  double endtime = YOLO;

  // quick parse argunemts
  if (argc > 1) {
    if (string(argv[1]) == "simple")
      model = test::Model01();
    else if (string(argv[1]) == "complex")
      model = test::Model02();
    else
      model = test::Model03();
  }
  else {
    // by default selec skiers lift model
    model = test::Model03();
  }
  if (argc > 2)
   istringstream (argv[2]) >> endtime;


  debug("main", "validating model");
  model->SetupAndValidate();

  debug("main", "preparing simulation");
  Simulation simulation = Simulation(model);
  simulation.SetEndtime(endtime);

  cout << "Running simulation..." << endl;
  simulation.Start();
  cout << "*Done*" << endl;

  simulation.PrintStats();
  return EXIT_SUCCESS;
}
