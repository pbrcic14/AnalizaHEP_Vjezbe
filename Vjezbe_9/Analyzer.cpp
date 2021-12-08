#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TF1.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void Analyzer::PlotHistogram(TString path)
{
	double tSum, tau;	
	
	TTree *tree = new TTree;
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(path);
	if (!f || !f->IsOpen())
	{
		f = new TFile(path);
	}
	f->GetObject("Tree",tree);
	Init(tree);
	
	if (fChain == 0)
		return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		
		histo->Fill(t);
		tSum += t;
	}
	
	tau = tSum / nentries;
	cout << "#tau = " << tau << endl;
}

// not used in task3
void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 2700, 900);
	c->Divide(3);
	
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	
	c->cd(1);
	
	func->SetLineColor(kBlue);
	func->SetTitle("Decay - maximum likelihood; #tau (s); number of atoms");
	func->Draw();
	
	c->cd(2);
	
	c->cd(3);
	
	c->SaveAs("Likelihood.png");
}










