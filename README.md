![C/C++ CI](https://github.com/MetaColon/Numericat/workflows/C/C++%20CI/badge.svg?branch=Develop)

# Numericat
Numerical solution of the Schrödinger equation for arbitrary potentials and visualisation of the results.

This project will consist of three parts:
* Parsing of an arbitrary one dimensional potential function (C)
* Numerically solving the time dependent Schrödinger equation by using the Crank-Nicolson method (C)
* Visualising the results (Java)

Currently functional:
* Parsing of functions (+,-,\*,/,^ with precedence and paranthesis support)
* Onedimensional solving of the Schrödinger equation
* Visualisation of the (onedimensional) results

Supported platforms:
* Linux
* MacOS
* Eventually Windows (not actively tested, some changes might have to be made to the Makefile)

## Use
Prerequisities:
* Make
* Some sort of C compiler (e.g. `gcc`)
* A Java 8 or higher JDK (e.g. OpenJDK 8)

Install using `make all` in root directory

Run using the executables or the run script - e.g.

```bash
% zsh run.sh "d(x-0.2)" "(1/(2*3.14159*0.005^2))^(1/4)*2.718^(0-(x-0.1)^2/(4*0.005^2))*2.718^(200000i*x)"
```
