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
    double value;
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
    double x;
    // double y;
    double t;
} Input;

double evaluate(Function func, Input in);
// Note that it's not really possible to test printing to the console
void printFunction(Function func);

#endif //BACKEND_FUNCTION_H
