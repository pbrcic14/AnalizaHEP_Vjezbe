#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TGraph.h>
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

void Analyzer::PlotHistogram(TString path)
{
	TTree *tree = new TTree;
	
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(path);
	if (!f || !f->IsOpen())
		f = new TFile(path);
	TDirectory * dir = (TDirectory*)f->Get(path+":/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);
	
	TLorentzVector* lep1 = new TLorentzVector();
	TLorentzVector* lep2 = new TLorentzVector();
	TLorentzVector* lep3 = new TLorentzVector();
	TLorentzVector* lep4 = new TLorentzVector();
	TLorentzVector* Z1 = new TLorentzVector();
	TLorentzVector* Z2 = new TLorentzVector();
	TLorentzVector* Higgs = new TLorentzVector();
	
	TFile* fw = new TFile(path); 
	TH1F* histoCounter = (TH1F*)fw->Get("ZZTree/Counters");
	
	double w, binContent;
	double sigDiscriminant;
	double bcgDiscriminant;
	double constant = 70.0;
	
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
		
		if(path.Contains("ggH125"))
		{
			sigDiscriminant = 1 / (1 + p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
			histoSignal->Fill(sigDiscriminant,w);
			histo2Dsig->Fill(Higgs->M(),sigDiscriminant,w);
		}
		else if(path.Contains("qqZZ"))
		{
			bcgDiscriminant = 1 / (1 + constant * p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
			histoBackground->Fill(bcgDiscriminant,w);
			histo2Dbcg->Fill(Higgs->M(),bcgDiscriminant,w);
		}
	}	
}

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	c->Divide(2,2);
	
	gPad->SetLeftMargin(0.15);
	
	c->cd(1);		// KinematicDiscriminant
	
	histoSignal->Scale(1.0/histoSignal->Integral());
	histoSignal->GetXaxis()->SetTitle("D_{kin}");
	histoSignal->GetYaxis()->SetTitle("Events / 0.02");
	histoSignal->GetYaxis()->SetRangeUser(0, 1);
	histoSignal->SetStats(0);
	histoSignal->SetLineColor(kRed);
	histoSignal->SetLineWidth(3);
	histoSignal->Draw("hist");
											
	histoBackground->Scale(1.0/histoBackground->Integral());
	histoBackground->GetXaxis()->SetTitle("D_{kin}");
	histoBackground->GetYaxis()->SetTitle("Events / 0.02");
	histoBackground->GetYaxis()->SetRangeUser(0, 1);
	histoBackground->SetStats(0);
	histoBackground->SetLineColor(kBlue);
	histoBackground->SetLineWidth(3);
	histoBackground->Draw("hist same");
	
	TLegend* legend = new TLegend(0.7,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histoSignal,"Signal","l");
	legend->AddEntry(histoBackground,"Background","l");
	legend->Draw();
	
	c->cd(2);		// ROC
	
	c->cd(3);		// Reconstructed mass vs KinematicDiscriminator (bcg)
	
	histo2Dbcg->SetTitle("m_{4l} vs D_{kin} for background");
	histo2Dbcg->GetXaxis()->SetTitle("m_{4l} (GeV)");
	histo2Dbcg->GetYaxis()->SetTitle("D_{kin}");
	histo2Dbcg->SetMinimum(-0.01);
	histo2Dbcg->SetStats(0);
	histo2Dbcg->Draw("COLZ");
	
	c->cd(4);		// Reconstructed mass vs KinematicDiscriminator (sig)
	
	histo2Dsig->SetTitle("m_{4l} vs D_{kin} for signal");
	histo2Dsig->GetXaxis()->SetTitle("m_{4l} (GeV)");
	histo2Dsig->GetYaxis()->SetTitle("D_{kin}");
	histo2Dsig->SetMinimum(-0.01);
	histo2Dsig->SetStats(0);
	histo2Dsig->Draw("COLZ");
	
	c->SaveAs("2DHistograms.png");
}







