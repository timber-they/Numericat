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

typedef enum AtomType{
    value,
    operator,
    variable,
    paranthesis,
    end
} AtomType;

typedef union Atom{
    double value;
    Operator op;
    Paranthesis paranthesis;
} Atom;

typedef struct Element {
    AtomType atomType;
    Atom atom;
} Element;

typedef Element *Function;

double evaluate(Function func, double in);
// Note that it's not really possible to test printing to the console
void printFunction(Function func);

#endif //BACKEND_FUNCTION_H
