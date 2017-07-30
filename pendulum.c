#include <stdio.h>
#include <math.h>

/* Simple program which simulates a swinging pendulum */
#define GRAVITY 9.8
#define PI 3.14159265

double thetadot(double u);

double udot(double theta, double l);

void update(double *theta, double *u, double thetanext, double unext);

int main(int argc, double argv[])
{
	double theta, theta0, thetanext;
	double u, u0, unext;
	double kt1, kt2, kt3, kt4;
	double ku1, ku2, ku3, ku4;
	double l, h;

	theta0 = 45;
	u0 = 0;
	l  = 10;
	h  = 1;

	double *iu;
	double *ith;

	iu = &u;
	ith = &theta;

	*iu = u0;
	*ith = theta0;

	printf("theta is: %lf\n", theta);
	printf("u is: %lf\n", u);
	printf("l is: %lf\n", l);
	printf("h is: %lf\n", h);

	for (int i = 0; i < 100; i++)
	{

		// Numerical Integration of 1st equation
		kt1 = thetadot(u);
		kt2 = thetadot(u + 0.5 * h * kt1);
		kt3 = thetadot(u + 0.5 * h * kt2);
		kt4 = thetadot(u + h * kt3);
		thetanext = theta + (h / 6) * (kt1 + 2 * kt2 + 2 * kt3 + kt4);

		// Numerical Integration of 2nd Equation
		ku1 = udot(theta, l);
		ku2 = udot(theta + 0.5 * h * ku1, l);
		ku3 = udot(theta + 0.5 * h * ku2, l);
		ku4 = udot(theta + h * ku3, l);
		unext = u + (h / 6) * (ku1 + 2 * ku2 + 2 * ku3 + ku4);

		//printf("%lf, %lf\n", thetanext, unext);
		printf("(x, y): (%lf, %lf)\n", l * cos(theta*PI/180), l * sin(theta*PI/180));
		// Probably need to use pointers... duh
		update(&theta, &u, thetanext, unext);

		printf("(x, y): (%lf, %lf)\n", l * cos(theta*PI/180), l * sin(theta*PI/180));

	}

	return 0;
}

double thetadot(double u)
{
	return u;
}

double udot(double theta, double l)
{
	return (-GRAVITY/ l) * sin(theta*(PI/180));
}

void update(double *theta, double *u, double thetanext, double unext) 
{
	*u = unext;
	*theta = thetanext;
}