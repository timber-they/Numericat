#ifndef BACKEND_FUNCTION_H
#define BACKEND_FUNCTION_H

typedef int bool;

typedef enum Operator{
    plus,   // +
    minus,  // -
    times,  // *
    divide  // /
} Operator;

typedef union Atom{
    double value;
    Operator operator;
} Atom;

typedef struct Element {
    // Indicates whether the Atom is a value or an operator
    bool isValue;
    Atom atom;
} Element;

typedef Element *Function;

#endif //BACKEND_FUNCTION_H
