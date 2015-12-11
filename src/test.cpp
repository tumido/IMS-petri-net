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

Model* test::Model02() {
  auto model = new Model;
  model->AddPlace("P1");
  model->AddPlace("P2");
  model->AddPlace("P3");
  model->AddPlace("P4");
  model->AddPlace("P5");
  model->AddPlace("P6");
  model->AddPlace("P7");
  model->AddPlace("P8");

  model->AddTransition("T1", 3, TransType::TimeGenerated);
  model->AddTransition("T2", 30);
  model->AddTransition("T3", 30);
  model->AddTransition("T4", 40);
  model->AddTransitionP("T5", 0);
  model->AddTransitionP("T6", 1);
  model->AddTransitionP("T7", 2);
  model->AddTransition("T8");
  model->AddTransition("T9");
  model->AddTransition("T10", 20);
  model->AddTransition("T11", 80);

  model->AddConnection("P1", "T1", ConnectionType::ToPlace);
  model->AddConnection("P1", "T2", ConnectionType::FromPlace);
  model->AddConnection("P1", "T3", ConnectionType::FromPlace);
  model->AddConnection("P1", "T4", ConnectionType::FromPlace);
  model->AddConnection("P2", "T2", ConnectionType::ToPlace);
  model->AddConnection("P2", "T5", ConnectionType::FromPlace);
  model->AddConnection("P2", "T11", ConnectionType::ToPlace);
  model->AddConnection("P3", "T2", ConnectionType::ToPlace);
  model->AddConnection("P3", "T5", ConnectionType::FromPlace);
  model->AddConnection("P3", "T6", ConnectionType::FromPlace);
  model->AddConnection("P4", "T3", ConnectionType::ToPlace);
  model->AddConnection("P4", "T6", ConnectionType::FromPlace);
  model->AddConnection("P4", "T7", ConnectionType::FromPlace);
  model->AddConnection("P5", "T4", ConnectionType::ToPlace);
  model->AddConnection("P5", "T7", ConnectionType::FromPlace);
  model->AddConnection("P6", "T5", ConnectionType::ToPlace);
  model->AddConnection("P6", "T8", ConnectionType::FromPlace);
  model->AddConnection("P7", "T6", ConnectionType::ToPlace);
  model->AddConnection("P7", "T9", ConnectionType::FromPlace);
  model->AddConnection("P8", "T7", ConnectionType::ToPlace);
  model->AddConnection("P8", "T10", ConnectionType::FromPlace);
  model->AddConnection("P8", "T11", ConnectionType::FromPlace);

  return model;
}
