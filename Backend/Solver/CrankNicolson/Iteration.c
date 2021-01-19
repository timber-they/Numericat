#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Iteration.h"


#define tMax 1
#define dx (M_PI/10) 
#define xf M_PI
#define xi 0
#define D 1.0
#define F 0.0
#define n 1.0

#define lambda .4
#define dt (lambda*dx*dx/D)

void CR() {
	int N = (int)((xf - xi) / dx), M = (int)(tMax / dt);
	double u[M + 1][N + 1];
	double a = 1 + lambda, b = -lambda / 2, c = -lambda / 2;
	double alpha[N], g[N];


	int  i, j, t;
	double k, l;
	for (i = 0; i <= N; i++)
		u[0][i] = U0((double)(i*dx)); 			//initializing u0
	for (i = 0; i <= M; i++) {				//initializing boundaries
		u[i][0] = 0;
		u[i][N] = 0;
	}							//implementing tridiagonal method
	alpha[0] = a;
	for (t = 1; t <= M; t++) {
		g[0] = ((1 - lambda)*u[t - 1][1] + (lambda / 2)*u[t - 1][0]);
		for (i = 1; i < N; i++) {
			alpha[i] = a - c*b / alpha[i - 1];
			g[i] = ((lambda / 2)*u[t - 1][i - 1] + (1 - lambda)*u[t - 1][i] + (lambda / 2)*u[t - 1][i + 1]) - b / alpha[i - 1] * g[i - 1];
		}

		u[t][N - 1] = g[N - 1] / alpha[N - 1];

		for (j = N - 2; j > 0; j--)
			u[t][j] = (g[j] - c*u[t][j + 1]) / alpha[j];
	}
	FILE *ft = fopen("t.csv", "w"), *fx = fopen("x.csv", "w"), *festimate = fopen("estimate.csv", "w"),
		*f_exact = fopen("exact.csv", "w"), *f_error = fopen("error.csv", "w");
	double error = 0.0;
	for (i = 0; i <= M; i++) {
		for (j = 0; j <= N; j++) {
			printf("%.8lf ", u[i][j]);
			fprintf(festimate, "%.8lf,", u[i][j]);
			if (i == 0 || i == M || j == 0 || j == N) {
				error = 0;
			}
			else {
				error = fabs((u[i][j] - (exact(j*dx, i*dt))) / u[i][j]) * 100;
			}
			fprintf(f_error, "%.8lf,", error);
		}
		printf("\n");
		fprintf(festimate, "\n");
		fprintf(f_error, "\n");
	}
	printf("\n\n");
	for (k = 0; k <= N; k++) {
		fprintf(ft, "%lf,", k);
	}
	for (k = 0; k <= M; k++) {
		fprintf(fx, "%lf\n", k);
	}
	for (k = 0; k <= M; k++) {
		for (l = 0; l <= N; l++) {
			printf("%.8lf ", exact(l*dx, k*dt));
			fprintf(f_exact, "%.8lf,", exact(l*dx, k*dt));
		}
		fprintf(f_exact, "\n");
		printf("\n");
	}
	fclose(ft);
	fclose(fx);
	fclose(festimate);
	fclose(f_error);
	fclose(f_exact);

}
double U0(double x) {
	return sin(n*x);
}

double exact(double x, double t) {
	return exp(-n*n*t)*sin(n*x);
}
