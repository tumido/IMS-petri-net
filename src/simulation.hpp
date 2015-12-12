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
#include "debug.hpp"
#include "stats.hpp"
#include <vector>
#include <iomanip>

class Simulation {
private:
    Calendar * calendar;
    Model * model;
    double simtime = 0;
    double endtime = 0;
public:
    Simulation(Model *);
    ~Simulation();
    void Start();
    void SetEndtime(double);
    void PlanEvents();
    void PlanGenerators();
    double GetSimtime() { return simtime; };
    Event * CreateEvent(Transition * );
    void PerformEvent(Event *);
    void DiscardEvent(Event *);
    void DeleteEvent(Event *);
    void CheckEvents();
    void PopToken(Token * t);
    void PrintStats();
};

#endif // __SIMULATION_HPP__
