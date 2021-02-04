#include "Complex.h"
#include <stdio.h>
#include <math.h>

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
Complex powerComplex(Complex a, Complex b)
{
    double a_arg = atan2(a.imaginary, a.real);
    double a_r = sqrt(a.real * a.real + a.imaginary * a.imaginary);
    return expComplex(sumComplex(multiplyComplex((Complex) {.real = log(a_r), .imaginary = 0}, b),
                                 multiplyComplex((Complex) {.real = 0, .imaginary = a_arg}, b)));
}
Complex expComplex(Complex b)
{
    return multiplyComplex((Complex) {.real = exp(b.real), .imaginary = 0},
                           (Complex) {.real = cos(b.imaginary), .imaginary = sin(b.imaginary)});
}
double absSquareComplex(Complex c)
{
    return c.real * c.real + c.imaginary * c.imaginary;
}
void printComplex(Complex c)
{
    printf("%lf %lfi  ", c.real, c.imaginary);
}
