#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <THStack.h>
#include <TString.h>
#include <vector>
#include <TLorentzVector.h>
#include <iostream>

void Analyzer::Loop()
{
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
   }
}

void Analyzer::PlotHistogram(TString name)
{
	TTree *tree = new TTree;
	
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/"+name+"/ZZ4lAnalysis.root");
	if (!f || !f->IsOpen())
		f = new TFile("/home/public/data/"+name+"/ZZ4lAnalysis.root");
	TDirectory * dir = (TDirectory*)f->Get("/home/public/data/"+name+"/ZZ4lAnalysis.root:/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);
	
	TLorentzVector* lep1 = new TLorentzVector();
	TLorentzVector* lep2 = new TLorentzVector();
	TLorentzVector* lep3 = new TLorentzVector();
	TLorentzVector* lep4 = new TLorentzVector();
	TLorentzVector* Z1 = new TLorentzVector();
	TLorentzVector* Z2 = new TLorentzVector();
	TLorentzVector* Higgs = new TLorentzVector();
	
	TFile fw("/home/public/data/"+name+"/ZZ4lAnalysis.root"); 
	TH1F* histoCounter = (TH1F*)fw.Get("ZZTree/Counters");
	
	funcQ->SetParNames("A", "B", "C");
	funcBW->SetParNames("D", "#Gamma", "M");
	funcQBW->SetParNames("A", "B", "C", "D", "#Gamma", "M");
	
	funcQ->SetParameters(9.57, -0.1262, 0.0004926);
	funcBW->SetParameters(2580.0, 820.3, 124.6);
	funcQBW->SetParameters(9.57, -0.1262, 0.0004926, 2580.0, 820.3, 124.6);
	// good attempt was 1.0, 0.01, -0.0001, 70.0, 200.0, 125.0
	
	double w, binContent;
	
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
		
		lep1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.0);
		lep2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.0);
		lep3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.0);
		lep4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.0);
			
		*Z1 = *lep1 + *lep2;
		*Z2 = *lep3 + *lep4;
		*Higgs = *Z1 + *Z2;
		
		binContent = histoCounter->GetBinContent(40);
		w = (137.0 * 1000.0 * xsec * overallEventWeight) / binContent;
		
		if(name == "ggH125")
			histoSignal->Fill(Higgs->M(),w);
		else if(name == "qqZZ")
			histoBackground->Fill(Higgs->M(),w);
	}
}

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 1800, 900);
	c->Divide(2);
	
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	
	c->cd(1);		// Theoretical model
	
	funcQBW->SetTitle("Theoretical model; M (GeV); Events");
	funcQBW->SetLineColor(kGreen);
	funcQBW->Draw();
	
	funcQ->SetLineColor(kBlue);
	funcQ->Draw("same");
	
	funcBW->SetLineColor(kRed);
	funcBW->Draw("same");
	
	TLegend* legend = new TLegend(0.5,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(funcQ,"Background (quadratic)","l");
	legend->AddEntry(funcBW,"Signal (Breit Wigner)","l");
	legend->AddEntry(funcQBW,"Background + signal","l");
	legend->Draw();
	
	c->cd(2);		// Data points with fit
	
	histoBackground->SetLineColor(kBlue);
	
	histoSignal->SetLineColor(kRed);
	histoSignal->Add(histoBackground);
	
	histoSignal->Draw("p E1 X0");
	histoSignal->SetTitle("Reconstructed mass; M (GeV); Events");
	histoSignal->Fit(funcQBW);
	
	c->SaveAs("Model.png");
}
