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
    // Indicates that the function is at its end
    bool end;
    Atom atom;
} Element;

typedef Element *Function;

double Evaluate(Function func, double in);
void Print(Function func);

#endif //BACKEND_FUNCTION_H
