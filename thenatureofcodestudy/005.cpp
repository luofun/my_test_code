#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<wingdi.h>

double montecarlo() {

	while (true) {

		double r1 = rand();
		r1 /= RAND_MAX;

		double probability = r1;

		double r2 = rand(); 
		r2 /= RAND_MAX;


		if (r2 < probability) {
			return r1;
		}
	}
}

void levy(double a, double b) {

	double stepsize = rand();
	stepsize = stepsize / RAND_MAX * (b - a);

	double stepx = rand();
	stepx = stepx / RAND_MAX * stepsize * 2 - stepsize;
	double stepy = rand();
	stepy = stepy / RAND_MAX * stepsize * 2 - stepsize;

	//x += stepx;
	//y += stepy;

}

void main() {
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		printf("%lf\n", montecarlo());
	}

	getchar();
}