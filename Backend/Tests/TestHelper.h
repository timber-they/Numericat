#include "../Parser/Function.h"
#include "../Solver/Types/Complex.h"
#include "../Solver/Types/Matrix.h"

#ifndef BACKEND_TESTHELPER_H
#define BACKEND_TESTHELPER_H

void assertFunctionsEq(char *function, Function expected, Function actual);
void assertComplexEq(Complex expected, Complex actual);
void assertFloatEq(double expected, double actual);
void assertMatrixEq(Matrix expected, Matrix actual);

#endif //BACKEND_TESTHELPER_H
