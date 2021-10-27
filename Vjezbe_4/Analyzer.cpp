#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <Analyzer.h>

using namespace std;

void Analyzer::readFile()
{
	ifstream file ("Analysis.txt");
	string line;
	int tmp;
	bool skip = true;
	
	while(getline(file, line))
	{
		if(skip)
		{
			skip = false;
			continue;
		}
		stringstream linestream(line);
		linestream >> tmp >> name1 >> p1[0] >> p1[1] >> p1[2] >> p1[3] >> name2 >> p2[0] >> p2[1] >> p2[2] >> p2[3];
	}
	
	file.close();
}
