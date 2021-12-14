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
	tSum = 0.0;
	
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
		
		N = nentries;
	}
}

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 2700, 900);
	c->Divide(3);
	gStyle->SetOptFit();
	
	c->cd(1);						// 
	gPad->SetLeftMargin(0.15);
	
	func->SetLineColor(kBlue);
	func->Draw();
	
	histo->SetLineColor(kRed);
	histo->SetTitle("Decay; #tau (s); number of atoms");
	histo->Draw("p E1 X0");
	histo->Fit(func);
	
	c->cd(2);						// 
	gPad->SetLeftMargin(0.15);
	
	func2->SetLineColor(kBlue);
	func2->SetTitle("Decay - maximum likelihood; #tau (s); number of atoms");
	func2->Draw();
	
	c->cd(3);						// 
	gPad->SetLeftMargin(0.15);
	
	func4->SetParameters(N,tSum);
	func4->SetLineColor(kBlue);
	func4->SetTitle("Decay; #tau (s); -2ln(L)");
	double min = func4->GetMinimumX();
	cout << "minimum is " << min << endl;
	func4->Draw();
	
	c->SaveAs("Likelihood.png");
}










