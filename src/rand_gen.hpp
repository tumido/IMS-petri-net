/**
 * @file simulation.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Library containing all functions that operates with randomness
 */
#ifndef __RAND_GEN_HPP__
#define __RAND_GEN_HPP__

#include <time.h>
#include <stdlib.h>
#include <random>

double GenerateDelayExp(double);
void RandomizeSeed();
int RollPercentage();

#endif // __RAND_GEN_HPP__