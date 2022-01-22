#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include <Analyzer.h>
#include <vector>

using namespace std;

int main()
{	
	Analyzer* thing;
	thing = new Analyzer();
	
	//thing->Loop();
	thing->Comparison("France", 164.7, 7.1);
	thing->Comparison("Italy", 166.1, 6.5);
	thing->Comparison("Netherlands", 170.3, 7.5);
	
	delete thing;
	return 0;
}
