/**
 * @file simulation.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Library containing all functions that operates with randomness
 */
#include "rand_gen.hpp"


double GenerateDelayExp(double) {
    return 0;
}

int RollPercentage() {
    return rand() % 100;
}
void RandomizeSeed() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    srand(t.tv_nsec);
}