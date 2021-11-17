#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
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

void Analyzer::PlotHistogram(TString name)
{
	TTree *tree = new TTree;
	
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/"+name+"/ZZ4lAnalysis.root");
	if (!f || !f->IsOpen())
		f = new TFile("/home/public/data/"+name+"/ZZ4lAnalysis.root");
	TDirectory * dir = (TDirectory*)f->Get("/home/public/data/"+name+"/ZZ4lAnalysis.root:/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);
	
	TCanvas* c = new TCanvas("c", "c", 2400, 1800);
	c->Divide(2,2);
	
	TH1F* histo11 = new TH1F("histo11", "Transversal Momentum", 200, 0, 150);
	TH1F* histo12 = new TH1F("histo12", "", 200, 0, 150);
	TH1F* histo13 = new TH1F("histo13", "", 200, 0, 150);
	TH1F* histo14 = new TH1F("histo14", "", 200, 0, 150);

	TH1F* histo21 = new TH1F("histo21", "Pseudorapidity", 100, -5, 5);
	TH1F* histo22 = new TH1F("histo22", "", 100, -5, 5);
	TH1F* histo23 = new TH1F("histo23", "", 100, -5, 5);
	TH1F* histo24 = new TH1F("histo24", "", 100, -5, 5);

	TH1F* histo31 = new TH1F("histo31", "Azimuth Angle", 100, -5, 5);
	TH1F* histo32 = new TH1F("histo32", "", 100, -5, 5);
	TH1F* histo33 = new TH1F("histo33", "", 100, -5, 5);
	TH1F* histo34 = new TH1F("histo34", "", 100, -5, 5);

	TH1F* histo41 = new TH1F("histo41", "Boosted Decision Tree", 40, 0, 10);
	TH1F* histo42 = new TH1F("histo42", "", 40, 0, 10);
	TH1F* histo43 = new TH1F("histo43", "", 40, 0, 10);
	TH1F* histo44 = new TH1F("histo44", "", 40, 0, 10);
	
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
		
		histo11->Fill(LepPt->at(2));
		histo12->Fill(LepPt->at(3));
		histo13->Fill(LepPt->at(0));
		histo14->Fill(LepPt->at(1));

		histo21->Fill(LepEta->at(2));
		histo22->Fill(LepEta->at(3));
		histo23->Fill(LepEta->at(0));
		histo24->Fill(LepEta->at(1));

		histo31->Fill(LepPhi->at(2));
		histo32->Fill(LepPhi->at(3));
		histo33->Fill(LepPhi->at(0));
		histo34->Fill(LepPhi->at(1));

		histo41->Fill(LepBDT->at(2));
		histo42->Fill(LepBDT->at(3));
		histo43->Fill(LepBDT->at(0));
		histo44->Fill(LepBDT->at(1));
	}
	
	c->cd(1);		// LepPt //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);
	
	histo11->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histo11->GetYaxis()->SetTitle("no. of events");
	histo11->SetStats(0);
	histo11->SetLineColor(kGreen);
	histo11->SetLineWidth(4);
	histo11->Draw();
	
	histo12->SetLineColor(kRed);
	histo12->SetLineWidth(2);
	histo12->Draw("hist same");
	
	histo13->SetLineColor(kOrange);
	histo13->SetLineWidth(4);
	histo13->Draw("hist same");
	
	histo14->SetLineColor(kBlue);
	histo14->SetLineWidth(2);
	histo14->Draw("hist same");
	
	TLegend* legend1 = new TLegend(0.7,0.7,0.9,0.9);
	legend1->SetTextSize(0.03);
	legend1->AddEntry(histo11,"Decay lepton 1","l");
	legend1->AddEntry(histo12,"Decay lepton 2","l");
	legend1->AddEntry(histo13,"Decay lepton 3","l");
	legend1->AddEntry(histo14,"Decay lepton 4","l");
	legend1->Draw();

	c->cd(2);		// LepEta //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);
	
	histo21->GetXaxis()->SetTitle("#eta");
	histo21->GetYaxis()->SetTitle("no. of events");
	histo21->SetStats(0);
	histo21->SetLineColor(kGreen);
	histo21->SetLineWidth(4);
	histo21->Draw();
	
	histo22->SetLineColor(kRed);
	histo22->SetLineWidth(2);
	histo22->Draw("hist same");
	
	histo23->SetLineColor(kOrange);
	histo23->SetLineWidth(4);
	histo23->Draw("hist same");
	
	histo24->SetLineColor(kBlue);
	histo24->SetLineWidth(2);
	histo24->Draw("hist same");
	
	TLegend* legend2 = new TLegend(0.7,0.7,0.9,0.9);
	legend2->SetTextSize(0.03);
	legend2->AddEntry(histo21,"Decay lepton 1","l");
	legend2->AddEntry(histo22,"Decay lepton 2","l");
	legend2->AddEntry(histo23,"Decay lepton 3","l");
	legend2->AddEntry(histo24,"Decay lepton 4","l");
	legend2->Draw();
	
	c->cd(3);		// LepPhi //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);
	
	histo31->GetXaxis()->SetTitle("#phi (rad)");
	histo31->GetYaxis()->SetTitle("no. of events");
	histo31->SetStats(0);
	histo31->SetLineColor(kGreen);
	histo31->SetLineWidth(4);
	histo31->Draw();
	
	histo32->SetLineColor(kRed);
	histo32->SetLineWidth(2);
	histo32->Draw("hist same");
	
	histo33->SetLineColor(kOrange);
	histo33->SetLineWidth(4);
	histo33->Draw("hist same");
	
	histo34->SetLineColor(kBlue);
	histo34->SetLineWidth(2);
	histo34->Draw("hist same");
	
	TLegend* legend3 = new TLegend(0.7,0.7,0.9,0.9);
	legend3->SetTextSize(0.03);
	legend3->AddEntry(histo31,"Decay lepton 1","l");
	legend3->AddEntry(histo32,"Decay lepton 2","l");
	legend3->AddEntry(histo33,"Decay lepton 3","l");
	legend3->AddEntry(histo34,"Decay lepton 4","l");
	legend3->Draw();
	
	c->cd(4);		// LepBDT //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);

	histo41->GetXaxis()->SetTitle("BDT");
	histo41->GetYaxis()->SetTitle("no. of events");
	histo41->SetStats(0);
	histo41->SetLineColor(kGreen);
	histo41->SetLineWidth(4);
	histo41->Draw();
	
	histo42->SetLineColor(kRed);
	histo42->SetLineWidth(2);
	histo42->Draw("hist same");
	
	histo43->SetLineColor(kOrange);
	histo43->SetLineWidth(4);
	histo43->Draw("hist same");
	
	histo44->SetLineColor(kBlue);
	histo44->SetLineWidth(2);
	histo44->Draw("hist same");
	
	TLegend* legend4 = new TLegend(0.7,0.7,0.9,0.9);
	legend4->SetTextSize(0.03);
	legend4->AddEntry(histo41,"Decay lepton 1","l");
	legend4->AddEntry(histo42,"Decay lepton 2","l");
	legend4->AddEntry(histo43,"Decay lepton 3","l");
	legend4->AddEntry(histo44,"Decay lepton 4","l");
	legend4->Draw();
	
	c->SaveAs("Leptons_"+name+".png");
}
