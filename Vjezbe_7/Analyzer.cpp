#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
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
	
	double w, binContent;
	
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	
	THStack* hs = new THStack("hs","Reconstructed mass");
	
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
			histo1->Fill(Higgs->M(),w);
		else if(name == "qqZZ")
			histo2->Fill(Higgs->M(),w);
	}
	
	gPad->SetLeftMargin(0.15);
	
	histo2->GetXaxis()->SetTitle("m_{4l} (GeV)");
	histo2->GetYaxis()->SetTitle("Events / 2GeV");
	histo2->SetStats(0);
	histo2->SetLineColor(kBlue);
	histo2->SetFillColor(kBlue);
	hs->Add(histo2);
	
	histo1->GetXaxis()->SetTitle("m_{4l} (GeV)");
	histo1->GetYaxis()->SetTitle("Events / 2GeV");
	histo1->SetStats(0);
	histo1->SetLineColor(kRed);
	histo1->SetFillColor(kRed);
	hs->Add(histo1);
	
	hs->Draw("hist");
	hs->GetXaxis()->SetTitle("m_{4l} (GeV)");
	hs->GetYaxis()->SetTitle("Events / 2GeV");
	
	TLegend* legend = new TLegend(0.7,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histo1,"Signal","f");
	legend->AddEntry(histo2,"Background","f");
	legend->Draw();
	
	c->SaveAs("Reconstructed.png");
}
