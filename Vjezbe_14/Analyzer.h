#define Analyzer_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <iostream>

class Analyzer
{
	public :
   
		virtual void Simulation();
		
		TH1F* histo = new TH1F("histo", "histo", 200, 0.0, 600.0);
		TH1F* histoChi = new TH1F("histoChi", "histoChi", 250, 0.0, 25.0);
		
		TF1* func = new TF1("func","[0]*exp(-x/[1])", 0.0, 300.0);
};
