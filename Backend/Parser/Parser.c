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

        finishNumber();

        if (handleOperator(raw[i]))
            return NULL;
    }

    finishNumber();
    func[j] = (Element) {.isValue=0, .end=1, .atom={0}};

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
                return 1;
            currentNumber += pow(10.0, currentNumberState) * val;
            currentNumberState--;
            break;
    }

    return 0;
}

int handleOperator(char val)
{
    if (j > 0 && !func[j-1].isValue)
        // Two operators in a row
        return 2;
    switch (val)
    {
        case '+':
            func[j++] = (Element) {.isValue=0, .end=0, .atom={plus}};
            break;
        case '-':
            func[j++] = (Element) {.isValue=0, .end=0, .atom={minus}};
            break;
        case '*':
            func[j++] = (Element) {.isValue=0, .end=0, .atom={times}};
            break;
        case '/':
            func[j++] = (Element) {.isValue=0, .end=0, .atom={divide}};
            break;
        default:
            return 1;
    }

    return 0;
}

void finishNumber()
{
    if (currentNumberState == 0)
        return;
    // Number is finished
    func[j++] = (Element) {.isValue=1, .end=0, .atom={currentNumber}};
    currentNumberState = 0;
    currentNumber = -1;
}
