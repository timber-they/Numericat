#include "../../Parser/Function.h"
#include "../Matrix/Utility.h"
#include "../Matrix/Complex.h"

#ifndef BACKEND_ITERATE_H
#define BACKEND_ITERATE_H

#define nx 1001
#define dx 0.001
#define dt 0.0001

/**
 * Iterate via the Crank-Nicolson method
 * @param function the function identifying the potential
 * @param dt the time steps used in the iteration
 * @param n the steps to iterate
 * @return an array containing the probability distribution for every given time step
 */
Complex **Iterate1d(Function potential, Function psi0, int n);

#endif //BACKEND_ITERATE_H
