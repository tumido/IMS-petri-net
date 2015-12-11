/**
 * @file test.cpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Testing class with premade models
 */

#include "test.hpp"

Model* test::Model01() {
  auto model = new Model;
  model->AddPlace("P1");
  model->AddPlace("P2");
  model->AddPlace("P3");
  model->AddPlace("P4");

  model->AddTransition("T1", 3, TransType::TimeGenerated);
  model->AddTransition("T2");
  model->AddTransition("T3", 5, TransType::TimeConstant);
  model->AddTransition("T4");

  model->AddConnection("P1", "T1", ConnectionType::ToPlace);
  model->AddConnection("P1", "T2", ConnectionType::FromPlace);
  model->AddConnection("P3", "T2", ConnectionType::ToPlace);
  model->AddConnection("P3", "T3", ConnectionType::FromPlace);
  model->AddConnection("P2", "T3", ConnectionType::ToPlace);
  model->AddConnection("P2", "T2", ConnectionType::FromPlace);
  model->AddConnection("P4", "T3", ConnectionType::ToPlace);
  model->AddConnection("P4", "T4", ConnectionType::FromPlace);

  model->AddToken("P2");

  return model;
}
