#include "../Solver/Types/Complex.h"

#ifndef BACKEND_FUNCTION_H
#define BACKEND_FUNCTION_H

typedef int bool;

typedef enum Operator{
    plus,       // +
    minus,      // -
    times,      // *
    divide,     // /
    power       // ^
} Operator;

typedef enum Paranthesis{
    open,       // (
    close       // )
} Paranthesis;

typedef enum Variable{
    variableX,
    // variableY,
    variableT
} Variable;

typedef enum AtomType{
    value,
    operator,
    variable,
    paranthesis,
    end
} AtomType;

typedef union Atom{
    Complex value;
    Operator op;
    Paranthesis paranthesis;
    Variable variable;
} Atom;

typedef struct Element {
    AtomType atomType;
    Atom atom;
} Element;

typedef Element *Function;

typedef struct Input{
    // Note that we don't expect to need comlex inputs
    double x;
    // double y;
    double t;
} Input;

Complex evaluate(Function func, Input in);
// Note that it's not really possible to test printing to the console
void printFunction(Function func);
int isTimeDependent(Function func);

#endif //BACKEND_FUNCTION_H
