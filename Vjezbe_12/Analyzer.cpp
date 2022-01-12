#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void Analyzer::Loop()
{
	TCanvas* c = new TCanvas("c", "c", 4800, 1800);
	c->Divide(4,2);
	
	TH1F* histoS1 = new TH1F("histoS1", "Transversal Momentum", 280, 0, 140);
	TH1F* histoB1 = new TH1F("histoB1", "Transversal Momentum", 280, 0, 140);
	
	Init(signal);	// signal //-------------------------------------------------------------------
   
	if (fChain == 0) return;
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
		
		histoS1->Fill(ele_pt);
	}
   
   Init(background);	// background //-----------------------------------------------------------
   
   if (fChain == 0) return;
	nentries = fChain->GetEntriesFast();
	nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		
		histoB1->Fill(ele_pt);
	}
	
	c->cd(1);			// ele_pt //---------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoB1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histoB1->GetYaxis()->SetTitle("no. of events");
	histoB1->SetStats(0);
	histoB1->SetLineColor(kBlue);
	histoB1->SetLineWidth(4);
	histoB1->Draw();
	
	histoS1->SetLineColor(kRed);
	histoS1->SetLineWidth(2);
	histoS1->Draw("hist same");
	
	c->SaveAs("ele_pt.png");
}











