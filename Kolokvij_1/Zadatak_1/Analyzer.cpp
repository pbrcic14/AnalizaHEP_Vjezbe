#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <Analyzer.h>

using namespace std;

Statistics::Statistics()
{
	cout << "Objekt je uspješno kreiran!" << endl;
}

void Statistics::CalculatePi(int N)
{
	random_device ran_dev;
	mt19937 gen(ran_dev());
	uniform_real_distribution<double> dist(0.0, 1.0);
	double x, y;
	double inCircle = 0.0;
	double pi = 0.0;
	
	for(int i = 0; i < N; i++)
	{
		x = dist(gen);
		y = dist(gen);
		
		if(sqrt(x*x+y*y) < 1)
			inCircle += 1.0;
	}
	
	pi = 4*inCircle/N;
	cout << "Pi = " << pi << endl;
}

void Statistics::NormalDistribution(double x, double mi, double sig)
{
	double P;
	double pi = 3.1415926;
	
	P = exp(-((x-mi)*(x-mi))/(2*sig*sig)) / (sig*sqrt(2*pi));
	cout << "P(" << x << ", " << mi << ", " << sig << ") = " << P << endl;
}
