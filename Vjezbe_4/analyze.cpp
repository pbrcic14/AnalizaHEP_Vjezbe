#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include <Analyzer.h>

using namespace std;

int main()
{	
	Analyzer* thing;
	thing = new Analyzer();
	
	//thing -> readFile();
	thing -> ConvertTxtToRootFile();
	
	delete thing;
	
	return 0;
}
