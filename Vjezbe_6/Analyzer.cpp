#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>

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

void Analyzer::PlotHistogram()
{
	TCanvas* c = new TCanvas("c", "c", 1800, 1800);
	c->Divide(2,2);
	
	TH1F* histo1 = new TH1F("histo1", "LepPt1", 100, 0, 150);
	TH1F* histo2 = new TH1F("histo2", "LepPt2", 100, 0, 150);
	TH1F* histo3 = new TH1F("histo3", "LepPt3", 100, 0, 150);
	TH1F* histo4 = new TH1F("histo4", "LepPt4", 100, 0, 150);
	
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
		
		histo1->Fill(LepPt->at(2));
		histo2->Fill(LepPt->at(3));
		histo3->Fill(LepPt->at(0));
		histo4->Fill(LepPt->at(1));
	}
	
	c->cd(1);		// LepPt
	
	histo1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histo1->GetYaxis()->SetTitle("no. of events");
	histo1->SetStats(0);
	histo1->SetLineColor(kRed);
	histo1->Draw();
	
	histo2->SetLineColor(kGreen);
	histo2->SetLineWidth(2);
	histo2->Draw("hist same");
	
	histo3->SetLineColor(kOrange);
	histo3->SetLineWidth(2);
	histo3->Draw("hist same");
	
	histo4->SetLineColor(kBlue);
	histo4->SetLineWidth(2);
	histo4->Draw("hist same");
	
	TLegend* legend = new TLegend(0.6,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histo1,"Decay lepton 1","f");
	legend->AddEntry(histo2,"Decay lepton 2","l");
	legend->AddEntry(histo3,"Decay lepton 3","l");
	legend->AddEntry(histo4,"Decay lepton 4","l");
	legend->Draw();
	
	//c->cd(2);		// LepEta
	//c->cd(3);		// LepPhi
	//c->cd(4);		// LepBDT
	
	c->SaveAs("tmp.pdf");
	c->SaveAs("tmp.png");
	c->SaveAs("tmp.root");
}
