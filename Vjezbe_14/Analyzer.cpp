#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLine.h>
#include <TStyle.h>
#include <TMath.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphPainter.h>
#include <TGraphErrors.h>
#include <TLine.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TRandom3.h>
#include <iostream>

using namespace std;

void Analyzer::Simulation()
{	
	TRandom3* r3 = new TRandom3();
	int N_measure = 100000, N_experiment = 1000;
	
	func->SetParName(0, "N_SM");
	func->SetParameter(0, 200);
	func->SetParName(1, "zeta_SM");
	func->FixParameter(1, 100);
	
	for(int i=0; i<N_experiment; i++)
	{
		for(int j=0; j<N_measure; j++)
		{
			histo->Fill(r3->Exp(100));
		}
		
		for(int k=0; k<580; k+=5)
		{
			histo->Fit(func, "q", "", k, k+20);
			histoChi->Fill(func->GetChisquare());
		}
		
		histo->Reset();
	}
	
	histoChi->Scale(1.0/histoChi->Integral());
	
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	gStyle->SetOptStat(0);
	
	histoChi->SetTitle("Test");
	histoChi->GetXaxis()->SetTitle("mPhotons");
	histoChi->GetYaxis()->SetTitle("PDF");
	histoChi->SetLineColor(kBlue);
	histoChi->SetLineWidth(2);
	histoChi->Draw("histo");
	
	c->SaveAs("Test.png");
}










