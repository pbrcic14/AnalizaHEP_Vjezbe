#include "Analyzer.h"
#include <TH2.h>
#include <TF1.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <iostream>

using namespace std;

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	gStyle->SetOptFit();
	
	const Int_t n = 5;
	Double_t y[n]  = {9.8, 21.2, 34.5, 39.9, 48.5};
	Double_t yErr[n]  = {1.0, 1.9, 3.1, 3.9, 5.1};
	Double_t x[n] = {1., 2., 3., 4., 5.};
	Double_t xErr[n] = {0., 0., 0., 0., 0.};
	
	TGraphErrors* gr = new TGraphErrors(n,x,y,xErr,yErr);
	gr->SetTitle("Acceleration vs force");
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->Draw("AP");
	
	TF1 *func;
	func = new TF1("func", "x/[0]" ,0.0, 5.0);
	func->SetParName(0, "mass");
	func->SetParameter(0, 1.0);
	gr->Fit(func);
	
	c->SaveAs("ChiSquare.png");
}
