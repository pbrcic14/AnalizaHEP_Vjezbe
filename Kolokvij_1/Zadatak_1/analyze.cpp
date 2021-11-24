#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <Analyzer.h>

using namespace std;

int main()
{		
	random_device ran_dev;
	mt19937 gen(ran_dev());
	uniform_real_distribution<double> dist(-100.0, 100.0);
	
	Statistics* s;
	s = new Statistics();
	
	s->CalculatePi(10000000);
	s->NormalDistribution(185, 178.2, 6.4);
	s->NormalDistribution(205, 178.2, 6.4);
	s->NormalDistribution(185, 160.2, 7.2);

	delete s;
	
	return 0;
}
