/**
 * @file simulation.hpp
 * @author Albert Uchytil, Tomas Coufal
 * @brief Library containing all functions that operates with randomness
 */
#include "rand_gen.hpp"


double GenerateDelayExp(double centre) {
    std::random_device rd;
    std::exponential_distribution<double> distrib(1/centre);
    std::mt19937 generator (rd ());
    double ret = distrib(generator);

    std::ostringstream s;
    s << "picking exp(" << centre << ") = " << ret;
    debug("rand", s.str());
    return ret;
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