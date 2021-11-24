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
	
	thing->PlotHistogram();
	thing->Drawing();
	
	delete thing;
	
	return 0;
}
