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
	const Int_t n = 5;
	Double_t y[n]  = {9.8, 21.2, 34.5, 39.9, 48.5};
	Double_t yErr[n]  = {1.0, 1.9, 3.1, 3.9, 5.1};
	Double_t x[n] = {1., 2., 3., 4., 5.};
	Double_t xErr[n] = {0., 0., 0., 0., 0.};
	
	TF1 *funcChi2;
	funcChi2 = new TF1("funcChi2", "pow((9.8-1.0*x)/1.0,2) + pow((21.2-2.0*x)/1.9,2) + pow((34.5-3.0*x)/3.1,2) +  pow((39.9-4.0*x)/3.9,2) + pow((48.5-5.0*x)/5.1,2)",0.0, 20.0);
	
	// task3
	double theta, x1, x2, sig1, sig2, mass, massSig1, massSig2;
	theta = funcChi2->GetMinimumX();
    x1 = funcChi2->GetX(funcChi2->GetMinimum() + 1.0, 1.0, funcChi2->GetMinimumX() - 0.0001);
    x2 = funcChi2->GetX(funcChi2->GetMinimum() + 1.0, funcChi2->GetMinimumX() + 0.0001, 20.0);
	sig1 = funcChi2->GetMinimumX() - x1;
	sig2 = x2 - funcChi2->GetMinimumX();
	mass = 1.0 / theta;
	massSig1 = sig1 / pow(theta,2);
	massSig2 = sig2 / pow(theta,2);
	cout << "FROM FUNCTION" << endl;
	cout << "Minimum at mass = " << mass << " +" << massSig1 << " -" << massSig2 << endl;
	
	// task2 (analytical)
	double numerator = 0.0, denominator = 0.0, thetaSig, massSig;
	for(int i=0; i<n; i++)
	{
		numerator += (x[i]*y[i]) / (yErr[i]*yErr[i]);
		denominator += (x[i]*x[i]) / (yErr[i]*yErr[i]);
	}
	theta = numerator / denominator;
	thetaSig = sqrt(2.0*denominator);
	mass = 1.0 / theta;
	massSig = thetaSig / (theta*theta);
	cout << "ANALYTICAL" << endl;
	cout << "Minimum at mass = " << mass << " +-" << massSig << endl;
}
