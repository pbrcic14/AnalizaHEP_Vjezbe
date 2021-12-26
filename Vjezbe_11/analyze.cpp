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
	Statistics* s;
	s = new Statistics();
	
	//s->Binomial(1, 0.800, 4);		// (r, p, N)
	//s->upperCP(2, 78, 0.6827); 	// (r, N, C)
	//s->lowerCP(2, 78, 0.6827);
	//s->Drawing(6);					// (r)
	s->RollDice(10, 0.6827);

	delete s;
	return 0;
}
