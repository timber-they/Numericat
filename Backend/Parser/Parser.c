#include "Parser.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// If no current number is known, this is 1, so that a lonely i means 1 negative unit
static double currentNumber;
// 0    -> No current number
// 1    -> Current number, no decimal point yet
// n<0  -> Current number, -nth digit after decimal point
// 2    -> Current number, imaginary unit (i) has already appeared (-> number is done)
static int currentNumberState;
static int j;
static Function func;

static int handleNumber(char val);

static int handleOperator(char val);

static void finishNumber();

static int handleVariable(char val);

static int handleParanthesis(char val);

static int validateEnd();

static void initialize();

static int isDigit(char c);

// TODO: This function is too long
Function parseFunction(char *raw)
{
    if (raw == NULL)
        return NULL;

    if (validateDyck(raw))
    {
        fprintf(stderr, "Not a valid Dyck language\n");
        return NULL;
    }

    initialize();

    size_t length = strlen(raw);
    func = malloc((length + 1) * sizeof(*func));

    for (int i = 0; i < length; i++)
    {
        if (raw[i] == ' ')
        {
            finishNumber();
            continue;
        }
        if (isDigit(raw[i]))
        {
            if (handleNumber(raw[i]))
            {
                free(func);
                return NULL;
            }
            continue;
        }

        if (raw[i] == 'x' || raw[i] == 't')
        {
            // For now only x and t - later maybe multiple dimensions
            if (handleVariable(raw[i]))
            {
                free(func);
                return NULL;
            }
            continue;
        }

        finishNumber();

        if (raw[i] == '(' || raw[i] == ')')
        {
            if (handleParanthesis(raw[i]))
            {
                free(func);
                return NULL;
            }
            continue;
        }

        if (handleOperator(raw[i]))
        {
            free(func);
            return NULL;
        }
    }

    finishNumber();
    if (validateEnd())
    {
        free(func);
        return NULL;
    }
    func[j] = (Element) {.atomType=end, .atom.value={0}};

    return func;
}


int validateDyck(char *in)
{
    int depth = 0;
    for (char *it = in; *it != '\0'; it++)
    {
        if (*it == '(')
            depth++;
        if (*it == ')')
            depth--;
        if (depth < 0)
            return depth;
    }

    return depth;
}

static int handleParanthesis(char val)
{
    switch (val)
    {
        case '(':
            if (j > 0 && func[j-1].atomType != operator && (func[j-1].atomType != paranthesis || func[j-1].atom.paranthesis != open))
            {
                fprintf(stderr, "Missing operator\n");
                return 2;
            }
            func[j++] = (Element) {.atomType=paranthesis, .atom.paranthesis = open};
            return 0;
        case ')':
            func[j++] = (Element) {.atomType=paranthesis, .atom.paranthesis = close};
            return 0;
        default:
            fprintf(stderr, "Unexpected paranthesis character: %c\n", val);
            return 1;
    }
}

static int validateEnd()
{
    if (j == 0)
    {
        fprintf(stderr, "Empty function not allowed\n");
        return 1;
    }
    if (func[j - 1].atomType == operator)
    {
        fprintf(stderr, "Function may not end with an operator\n");
        return 1;
    }

    return 0;
}

static int handleNumber(char val)
{
    if (currentNumberState != 2 && val == 'i')
    {
        currentNumberState = 2;
        return 0;
    }
    if (val == '.')
    {
        if (currentNumberState != 1)
        {
            return 5;
        }
        currentNumberState = -1;
        return 0;
    }

    int number = val - '0';

    switch (currentNumberState)
    {
        case 0:
            if (j > 0 && func[j - 1].atomType == value)
            {
                fprintf(stderr, "A number can't follow a number\n");
                return 2;
            }
            if (j > 0 && func[j - 1].atomType == variable)
            {
                fprintf(stderr, "A number can't follow a variable\n");
                return 3;
            }
            currentNumberState = 1;
            currentNumber = number;
            break;
        case 1:
            currentNumber = currentNumber * 10 + number;
            break;
        case 2:
            fprintf(stderr, "Imaginary unit can't be inside a number (it has to be at the end)\n");
            return 4;
        default:
            if (currentNumberState > 0)
            {
                fprintf(stderr, "Unexpected number state: %d\n", currentNumberState);
                return 1;
            }
            currentNumber += pow(10.0, currentNumberState) * number;
            currentNumberState--;
            break;
    }

    return 0;
}

static int handleOperator(char val)
{
    if (j > 0 && func[j - 1].atomType == operator)
    {
        fprintf(stderr, "Two operators in a row (parsing %c)\n", val);
        return 2;
    }
    switch (val)
    {
        case '+':
            func[j++] = (Element) {.atomType=operator, .atom.op=plus};
            break;
        case '-':
            func[j++] = (Element) {.atomType=operator, .atom.op=minus};
            break;
        case '*':
            func[j++] = (Element) {.atomType=operator, .atom.op=times};
            break;
        case '/':
            func[j++] = (Element) {.atomType=operator, .atom.op=divide};
            break;
        case '^':
            func[j++] = (Element) {.atomType=operator, .atom.op=power};
            break;
        default:
            fprintf(stderr, "Unexpected operator: %c\n", val);
            return 1;
    }

    return 0;
}

static void finishNumber()
{
    if (currentNumberState == 0)
        // No number to finish
        return;
    // Number is finished
    if (currentNumberState == 2)
        func[j++] = (Element) {.atomType=value, .atom.value=(Complex) {.real = 0, .imaginary = currentNumber}};
    else
        func[j++] = (Element) {.atomType=value, .atom.value=(Complex) {.real = currentNumber, .imaginary = 0}};
    currentNumberState = 0;
    currentNumber = 1;
}

static int handleVariable(char val)
{
    if (currentNumberState != 0 || (j > 0 && func[j - 1].atomType == value))
    {
        fprintf(stderr, "A variable can't follow a number\n");
        return 1;
    }
    if (j > 0 && func[j - 1].atomType == variable)
    {
        fprintf(stderr, "A variable can't follow a variable\n");
        return 2;
    }

    switch(val)
    {
        case 'x':
            func[j++] = (Element) {.atomType=variable, .atom.variable=variableX};
            return 0;
        case 't':
            func[j++] = (Element) {.atomType=variable, .atom.variable=variableT};
            return 0;
        default:
            fprintf(stderr, "Unexpected variable: %c\n", val);
            return 3;
    }
}

static void initialize()
{
    currentNumber = 1;
    currentNumberState = 0;
    j = 0;
}

static int isDigit(char c)
{
    return (c >= '0' && c <= '9') || c == 'i' || c == '.';
}

