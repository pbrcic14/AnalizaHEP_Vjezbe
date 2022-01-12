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
	
	TH1F* histoS1 = new TH1F("histoS1", "ele_pt", 240, 0, 120);
	TH1F* histoB1 = new TH1F("histoB1", "ele_pt", 240, 0, 120);
	TH1F* histoS2 = new TH1F("histoS2", "scl_eta", 60, -3, 3);
	TH1F* histoB2 = new TH1F("histoB2", "scl_eta", 60, -3, 3);
	TH1F* histoS3 = new TH1F("histoS3", "ele_hadronicOverEm", 40, 0, 0.2);
	TH1F* histoB3 = new TH1F("histoB3", "ele_hadronicOverEm", 40, 0, 0.2);
	TH1F* histoS4 = new TH1F("histoS4", "ele_gsfchi2", 100, 0, 10);
	TH1F* histoB4 = new TH1F("histoB4", "ele_gsfchi2", 100, 0, 10);
	TH1F* histoS5 = new TH1F("histoS5", "ele_fbrem", 80, -2, 2);
	TH1F* histoB5 = new TH1F("histoB5", "ele_fbrem", 80, -2, 2);
	TH1F* histoS6 = new TH1F("histoS6", "ele_ep", 80, 0, 8);
	TH1F* histoB6 = new TH1F("histoB6", "ele_ep", 80, 0, 8);
	TH1F* histoS7 = new TH1F("histoS7", "ele_eelepout", 210, 0, 21);
	TH1F* histoB7 = new TH1F("histoB7", "ele_eelepout", 210, 0, 21);
	TH1F* histoS8 = new TH1F("histoS8", "ele_pfChargedHadIso", 90, 0, 3);
	TH1F* histoB8 = new TH1F("histoB8", "ele_pfChargedHadIso", 90, 0, 3);
	
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
		histoS2->Fill(scl_eta);
		histoS3->Fill(ele_hadronicOverEm);
		histoS4->Fill(ele_gsfchi2);
		histoS5->Fill(ele_fbrem);
		histoS6->Fill(ele_ep);
		histoS7->Fill(ele_eelepout);
		histoS8->Fill(ele_pfChargedHadIso);
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
		histoB2->Fill(scl_eta);
		histoB3->Fill(ele_hadronicOverEm);
		histoB4->Fill(ele_gsfchi2);
		histoB5->Fill(ele_fbrem);
		histoB6->Fill(ele_ep);
		histoB7->Fill(ele_eelepout);
		histoB8->Fill(ele_pfChargedHadIso);
	}
	
	c->cd(1);			// ele_pt //----------------------------------------------------------------
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
	
	c->cd(2);			// scl_eta //---------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS2->GetXaxis()->SetTitle("scl_eta");
	histoS2->GetYaxis()->SetTitle("no. of events");
	histoS2->SetStats(0);
	histoS2->SetLineColor(kRed);
	histoS2->SetLineWidth(4);
	histoS2->Draw();
	
	histoB2->SetLineColor(kBlue);
	histoB2->SetLineWidth(2);
	histoB2->Draw("hist same");
	
	c->cd(3);			// ele_hadronicOverEm //----------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS3->GetXaxis()->SetTitle("ele_hadronicOverEm");
	histoS3->GetYaxis()->SetTitle("no. of events");
	histoS3->SetStats(0);
	histoS3->SetLineColor(kRed);
	histoS3->SetLineWidth(4);
	histoS3->Draw();
	
	histoB3->SetLineColor(kBlue);
	histoB3->SetLineWidth(2);
	histoB3->Draw("hist same");
	
	c->cd(4);			// ele_gsfchi2 //-----------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS4->GetXaxis()->SetTitle("ele_gsfchi2");
	histoS4->GetYaxis()->SetTitle("no. of events");
	histoS4->SetStats(0);
	histoS4->SetLineColor(kRed);
	histoS4->SetLineWidth(4);
	histoS4->Draw();
	
	histoB4->SetLineColor(kBlue);
	histoB4->SetLineWidth(2);
	histoB4->Draw("hist same");
	
	c->cd(5);			// ele_fbrem //-------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS5->GetXaxis()->SetTitle("ele_fbrem");
	histoS5->GetYaxis()->SetTitle("no. of events");
	histoS5->SetStats(0);
	histoS5->SetLineColor(kRed);
	histoS5->SetLineWidth(4);
	histoS5->Draw();
	
	histoB5->SetLineColor(kBlue);
	histoB5->SetLineWidth(2);
	histoB5->Draw("hist same");
	
	c->cd(6);			// ele_ep //----------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS6->GetXaxis()->SetTitle("ele_ep");
	histoS6->GetYaxis()->SetTitle("no. of events");
	histoS6->SetStats(0);
	histoS6->SetLineColor(kRed);
	histoS6->SetLineWidth(4);
	histoS6->Draw();
	
	histoB6->SetLineColor(kBlue);
	histoB6->SetLineWidth(2);
	histoB6->Draw("hist same");
	
	c->cd(7);			// ele_eelepout //----------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS7->GetXaxis()->SetTitle("ele_eelepout");
	histoS7->GetYaxis()->SetTitle("no. of events");
	histoS7->SetStats(0);
	histoS7->SetLineColor(kRed);
	histoS7->SetLineWidth(4);
	histoS7->Draw();
	
	histoB7->SetLineColor(kBlue);
	histoB7->SetLineWidth(2);
	histoB7->Draw("hist same");
	
	c->cd(8);			// ele_pfChargedHadIso //---------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS8->GetXaxis()->SetTitle("ele_pfChargedHadIso");
	histoS8->GetYaxis()->SetTitle("no. of events");
	histoS8->SetStats(0);
	histoS8->SetLineColor(kRed);
	histoS8->SetLineWidth(4);
	histoS8->Draw();
	
	histoB8->SetLineColor(kBlue);
	histoB8->SetLineWidth(2);
	histoB8->Draw("hist same");
	
	c->SaveAs("ElectronVariables.png");
}






