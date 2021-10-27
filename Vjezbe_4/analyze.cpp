#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <Analyzer.h>

using namespace std;

int main()
{	
	Analyzer* thing;
	thing = new Analyzer();
	
	thing -> readFile();
	
	delete thing;
	
	return 0;
}
