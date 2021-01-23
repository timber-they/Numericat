#include "Complex.h"
#include <stdio.h>

Complex sumComplex(Complex a, Complex b)
{
    return (Complex) {.real = a.real + b.real, .imaginary = a.imaginary + b.imaginary};
}
Complex subtractComplex(Complex a, Complex b)
{
    return (Complex) {.real = a.real - b.real, .imaginary = a.imaginary - b.imaginary};
}
Complex multiplyComplex(Complex a, Complex b)
{
    return (Complex) {.real = a.real * b.real - a.imaginary * b.imaginary,
                      .imaginary = a.real * b.imaginary + a.imaginary * b.real};
}
Complex divideComplex(Complex a, Complex b)
{
    double division = b.real * b.real + b.imaginary * b.imaginary;
    return (Complex) {.real = (a.real * b.real + a.imaginary * b.imaginary) / division,
                      .imaginary = (a.imaginary * b.real - a.real * b.imaginary) / division};
}
double absSquareComplex(Complex c)
{
    return c.real * c.real + c.imaginary * c.imaginary;
}
void printComplex(Complex c)
{
    printf("%lf %lfi  ", c.real, c.imaginary);
}
