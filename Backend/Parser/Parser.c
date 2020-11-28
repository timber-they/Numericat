#include "Parser.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static double currentNumber = -1;
// 0    -> No current number
// 1    -> Current number, no decimal point yet
// n<0  -> Current number, -nth digit after decimal point
static int currentNumberState = 0;
static int j = 0;
static Function func;

int handleNumber(int val);

int handleOperator(char val);

void finishNumber();

int handleVariable(char val);

Function Parse(char *raw)
{
    size_t length = strlen(raw);
    func = malloc((length + 1) * sizeof(*func));

    for (int i = 0; i < length; i++)
    {
        if (raw[i] == ' ')
            continue;
        if (raw[i] >= '0' && raw[i] <= '9')
        {
            int val = raw[i] - '0';
            if (handleNumber(val))
                return NULL;
            continue;
        }

        if (raw[i] == '.')
        {
            if (currentNumberState != 1)
                return NULL;
            currentNumberState = -1;
            continue;
        }

        if (raw[i] == 'x')
        {
            // For now only x - later maybe multiple dimensions
            if (handleVariable(raw[i]))
                return NULL;
            continue;
        }

        finishNumber();

        if (handleOperator(raw[i]))
            return NULL;
    }

    finishNumber();
    func[j] = (Element) {.atomType=end, .atom.value=0};

    return func;
}

int handleNumber(int val)
{
    switch (currentNumberState)
    {
        case 0:
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

int handleOperator(char val)
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
        default:
            fprintf(stderr, "Unexpected operator: %c\n", val);
            return 1;
    }

    return 0;
}

void finishNumber()
{
    if (currentNumberState == 0)
        // No number to finish
        return;
    // Number is finished
    func[j++] = (Element) {.atomType=value, .atom.value=currentNumber};
    currentNumberState = 0;
    currentNumber = -1;
}

int handleVariable(__attribute__((unused)) char val)
{
    if (currentNumberState != 0)
    {
        fprintf(stderr, "A variable can't follow a number\n");
        return 1;
    }
    if (j > 0 && func[j-1].atomType == variable)
    {
        fprintf(stderr, "A variable can't follow a variable\n");
        return 2;
    }

    func[j++] = (Element) {.atomType=variable, .atom.value=-1};
    return 0;
}
