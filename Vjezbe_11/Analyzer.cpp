#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <TMath.h>
#include <TH1F.h>
#include <cstdlib>
#include <TStyle.h>
#include <TColor.h>
#include <TLine.h>
#include <TCanvas.h>
#include <ctime>
#include <random>
#include <Analyzer.h>

using namespace std;

Statistics::Statistics(){}

double Statistics::Binomial(int r, double p, int N)
{	
	double B;
	B = TMath::Factorial(N) * pow(p,r) * pow(1-p,N-r) / (TMath::Factorial(r) * TMath::Factorial(N-r));
	//cout << "Binomial(" << r << "; " << p << ", " << N << ") = " << B << endl;
	return B;
}

double Statistics::upperCP(int r, int N, double C)
{	
	double p = 1.0;
	double sumB = 1.0;
	while((1.0-sumB) < ((1.0-C)/2.0))
	{
		//cout << 1.0-sumB << " < " << (1.0-C)/2.0 << endl;
		sumB = 0.0;
		for(int j=r+1; j<=N; j++)
		{
			sumB += Binomial(j, p, N);
		}
		p -= 0.001;
	}
	//cout << "Upper limit " << p << endl;
	return p;
}

double Statistics::lowerCP(int r, int N, double C)
{	
	double p = 1.0;
	double sumB;
	double sum = 100.0;
	
	if(r==0)
		return 0.0;
	
	while(sum > ((1.0-C)/2.0))
	{
		//cout << 1.0-sumB << " > " << (1.0-C)/2.0 << endl;
		sumB = 0.0;
		for(int j=0; j<r; j++)
		{
			sumB += Binomial(j, p, N);
		}
		p -= 0.001;
		sum = 1.0 - sumB;
	}
	//cout << "Lower limit " << p << endl;
	return p;
}

void Statistics::Drawing(int rDraw)
{	
	int N = 10;
	double C = 0.6827;
	double lower, upper;
	
	TH1F *lowerHisto;
	TH1F *upperHisto;
	lowerHisto = new TH1F("smth1", "smth1", 10, 0.0, 10.0);
	upperHisto = new TH1F("smth2", "smth2", 10, 0.0, 10.0);
	
	for(int r=0; r<=N; r++)
	{
		lower = lowerCP(r, N, C);
		upper = upperCP(r, N, C);
		
		lowerHisto->SetBinContent(r,lower);
		upperHisto->SetBinContent(r,upper);
	}
	
	TCanvas *c;
	c = new TCanvas("c","c",900,900);
	gStyle->SetOptStat(0);
	
	upperHisto->SetTitle("Neyman confidence belt; n; p");
	upperHisto->GetYaxis()->SetRangeUser(0.0,1.0);
	lowerHisto->GetYaxis()->SetRangeUser(0.0,1.0);
	
	Int_t color = TColor::GetFreeColorIndex();
	
	upperHisto->SetLineColor(kBlue);
	upperHisto->SetFillColor(kBlue);
	lowerHisto->SetLineColor(0);
	lowerHisto->SetFillColor(color);
	
	upperHisto->Draw();
	lowerHisto->Draw("same");
	
	TLine *l = new TLine(rDraw, 0.0, rDraw, upperCP(rDraw, N, C));
	l->SetLineStyle(2);
	l->Draw();
	TLine *l1 = new TLine(0.0, lowerCP(rDraw, N, C), rDraw, lowerCP(rDraw, N, C));
	l1->SetLineStyle(2);
	l1->Draw();
	TLine *l2 = new TLine(0.0, upperCP(rDraw, N, C), rDraw, upperCP(rDraw, N, C));
	l2->SetLineStyle(2);
	l2->Draw();
	
	c->SaveAs("CP.png");
}

void Statistics::RollDice(int N, double C)
{
	srand(time(NULL));
	int counter, r = 0;
	double upper, lower;

	for (int i=0; i<1000; i++)
	{
		counter = 0;
		for(int j=0; j<N; j++)
			if(rand()%6 == 0)
				counter++;
		
		upper = upperCP(counter, N, C);
		lower = lowerCP(counter, N, C);

		if(upper >= (1.0/6.0) && lower <= (1.0/6.0))
			r++;
	}
	
	cout << "Number of experiments with true value for 10 rolls is " << r << " in interval " << C << endl;
}






