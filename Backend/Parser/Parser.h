#include "Function.h"

#ifndef BACKEND_PARSER_H
#define BACKEND_PARSER_H

Function Parse(char *raw);
double Evaluate(Function func, double in);

#endif //BACKEND_PARSER_H
