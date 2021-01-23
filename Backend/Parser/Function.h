#ifndef BACKEND_FUNCTION_H
#define BACKEND_FUNCTION_H

typedef int bool;

typedef enum Operator{
    plus,       // +
    minus,      // -
    times,      // *
    divide,     // /
} Operator;

typedef enum AtomType{
    value,
    operator,
    variable,
    end
} AtomType;

typedef union Atom{
    double value;
    Operator op;
} Atom;

typedef struct Element {
    AtomType atomType;
    Atom atom;
} Element;

typedef Element *Function;

double Evaluate(Function func, double in);
// Note that it's not really possible to test printing to the console
void Print(Function func);

#endif //BACKEND_FUNCTION_H
