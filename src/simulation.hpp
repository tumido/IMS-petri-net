/**
 * @file simulation.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Class which takes care of the simulation
 */
#ifndef __SIMULATION_HPP__
#define __SIMULATION_HPP__

#include "calendar.hpp"
#include "model.hpp"
#include "event.hpp"
#include "transition.hpp"
#include "rand_gen.hpp"
#include "probtrans.hpp"
#include <vector>

class Simulation {
private:
    Calendar * calendar;
    Model * model;
    double simtime;
    double endtime;
public:
    Simulation();
    ~Simulation();
    void Start();
    void SetEndtime(double);
    void PlanEvents();
    double GetSimtime() { return simtime; };
    Event * CreateEvent(Transition * );
    void PerformEvent(Event *);
    void DiscardEvent(Event *);
    void CheckEvents();
};

#endif // __SIMULATION_HPP__
