#include "../../Parser/Function.h"
#include "../Matrix/Utility.h"

#ifndef BACKEND_ITERATE_H
#define BACKEND_ITERATE_H

#define nx 1001

/**
 * Iterate via the Crank-Nicolson method
 * @param function the function identifying the potential
 * @param dt the time steps used in the iteration
 * @param n the steps to iterate
 * @return an array containing the probability distribution for every given time step
 */
double **Iterate1d(Function potential, Function psi0, double dt, int n);

#endif //BACKEND_ITERATE_H
