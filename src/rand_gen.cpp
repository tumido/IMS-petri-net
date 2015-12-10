/**
 * @file simulation.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Library containing all functions that operates with randomness
 */
#include "rand_gen.hpp"


double GenerateDelayExp(double centre) {
    std::default_random_engine generator;
    std::exponential_distribution<double> distrib(centre);
    debug("rand", "picking exponential distribution");
    return distrib(generator);
}

int RollPercentage() {
    debug("rand", "percentage roll");
    return rand() % 100;
}
void RandomizeSeed() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    srand(t.tv_nsec);
    debug("rand", "seed set");
}