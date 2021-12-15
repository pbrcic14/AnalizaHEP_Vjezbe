#include "Analyzer.h"
#include <TH2.h>
#include <TF1.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <iostream>
#include <TMath.h>

using namespace std;

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 2000, 900);
	c->Divide(2);
	gStyle->SetOptFit();
	
	const Int_t n = 5;
	Double_t y[n]  = {9.8, 21.2, 34.5, 39.9, 48.5};
	Double_t yErr[n]  = {1.0, 1.9, 3.1, 3.9, 5.1};
	Double_t x[n] = {1., 2., 3., 4., 5.};
	Double_t xErr[n] = {0., 0., 0., 0., 0.};
	
	c->cd(1);						// 
	
	TGraphErrors* gr = new TGraphErrors(n,x,y,xErr,yErr);
	gr->SetTitle("Acceleration vs force; F (N); a (m/s^{2})");
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->Draw("AP");
	
	TF1 *func;
	func = new TF1("func", "x/[0]" ,0.0, 5.0);
	func->SetParName(0, "mass");
	func->SetParameter(0, 1.0);
	gr->Fit(func);
	
	c->cd(2);						// 
	
	TF1 *funcChi2;
	funcChi2 = new TF1("funcChi2", "pow((9.8-1.0*x)/1.0,2) + pow((21.2-2.0*x)/1.9,2) + pow((34.5-3.0*x)/3.1,2) +  pow((39.9-4.0*x)/3.9,2) + pow((48.5-5.0*x)/5.1,2)",0.0, 20.0);
	funcChi2->SetTitle("Chi-square; x; y");
	funcChi2->Draw();
	
	double theta = funcChi2->GetMinimumX();
    double x1 = funcChi2->GetX(funcChi2->GetMinimum() + 1.0, 1.0, funcChi2->GetMinimumX() - 0.0001);
    double x2 = funcChi2->GetX(funcChi2->GetMinimum() + 1.0, funcChi2->GetMinimumX() + 0.0001, 20.0);
	double sig1 = funcChi2->GetMinimumX() - x1;
	double sig2 = x2 - funcChi2->GetMinimumX();
	double mass = 1.0 / theta;
	double massSig1 = sig1 / pow(theta,2);
	double massSig2 = sig2 / pow(theta,2);
	cout << "Minimum at mass = " << mass << " +" << massSig1 << " -" << massSig2 << endl;
	
	c->SaveAs("ChiSquare.png");
}
