#include "Parser.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static double currentNumber;
// 0    -> No current number
// 1    -> Current number, no decimal point yet
// n<0  -> Current number, -nth digit after decimal point
static int currentNumberState;
static int j;
static Function func;

static int handleNumber(int val);

static int handleOperator(char val);

static void finishNumber();

static int handleVariable(char val);

static int handleParanthesis(char val);

static int validateEnd();

static void initialize();

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
        if (raw[i] >= '0' && raw[i] <= '9')
        {
            int val = raw[i] - '0';
            if (handleNumber(val))
            {
                free(func);
                return NULL;
            }
            continue;
        }

        if (raw[i] == '.')
        {
            if (currentNumberState != 1)
            {
                free(func);
                return NULL;
            }
            currentNumberState = -1;
            continue;
        }

        if (raw[i] == 'x')
        {
            // For now only x - later maybe multiple dimensions
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
    switch(val)
    {
        case '(':
            if (j > 0 && func[j-1].atomType != operator)
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
    if (func[j-1].atomType == operator)
    {
        fprintf(stderr, "Function may not end with an operator\n");
        return 1;
    }

    return 0;
}

static int handleNumber(int val)
{
    switch (currentNumberState)
    {
        case 0:
            if (j > 0 && func[j-1].atomType == value)
            {
                fprintf(stderr, "A number can't follow a number\n");
                return 2;
            }
            if (j > 0 && func[j-1].atomType == variable)
            {
                fprintf(stderr, "A number can't follow a variable\n");
                return 3;
            }
            currentNumberState = 1;
            currentNumber = val;
            break;
        case 1:
            currentNumber = currentNumber * 10 + val;
            break;
        default:
            if (currentNumberState > 0)
            {
                fprintf(stderr, "Unexpected number state: %d\n", currentNumberState);
                return 1;
            }
            currentNumber += pow(10.0, currentNumberState) * val;
            currentNumberState--;
            break;
    }

    return 0;
}

static int handleOperator(char val)
{
    if (j > 0 && func[j-1].atomType == operator)
    {
        fprintf(stderr, "Two operators in a row\n");
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
    // TODO: Complex
    func[j++] = (Element) {.atomType=value, .atom.value=(Complex) {.real = currentNumber, .imaginary = 0}};
    currentNumberState = 0;
    currentNumber = -1;
}

static int handleVariable(__attribute__((unused)) char val)
{
    if (currentNumberState != 0 || (j > 0 && func[j-1].atomType == value))
    {
        fprintf(stderr, "A variable can't follow a number\n");
        return 1;
    }
    if (j > 0 && func[j-1].atomType == variable)
    {
        fprintf(stderr, "A variable can't follow a variable\n");
        return 2;
    }

    func[j++] = (Element) {.atomType=variable, .atom.value={.real = -1, .imaginary = 0}};
    return 0;
}

static void initialize()
{
    currentNumber = -1;
    currentNumberState = 0;
    j = 0;
}

