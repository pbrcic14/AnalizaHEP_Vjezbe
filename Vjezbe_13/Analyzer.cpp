#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLine.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TRandom1.h>
#include <iostream>

using namespace std;

void Analyzer::Loop()
{
	// simulation //
	
	TRandom1* rand = new TRandom1();
	int N_measure = 100, N_experiment = 1000000;
	double heightSum, testStatistic;
	
	for(int i=0; i<N_experiment; i++)
	{
		heightSum = 0.0;
		
		for(int j=0; j<N_measure; j++)
			heightSum += rand->Gaus(164.7, 7.1);
		
		testStatistic = heightSum/N_measure;
		histoTestStatistic->Fill(testStatistic);
	}
	
	// data and test statistic //
	
	double dataSum = 0.0, dataAverage, p, z;
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
		
		histoHeight->Fill(height);
		dataSum += height;
	}
   
	dataAverage = dataSum/nentries;
	histoTestStatistic->Scale(1/histoTestStatistic->Integral());
	
	if(dataAverage > 164.7)
	{
		p = histoTestStatistic->Integral(histoTestStatistic->FindBin(dataAverage), 500);
		z = TMath::Sqrt(2)*TMath::ErfcInverse(2*p);
		cout << "p = " << p << endl;
		cout << "z = " << z << endl;
	}
	else
	{
		p = histoTestStatistic->Integral(0, histoTestStatistic->FindBin(dataAverage));
		z = TMath::Sqrt(2)*TMath::ErfcInverse(2*p);
		cout << "p = " << p << endl;
		cout << "z = " << z << endl;
	}
   
	// plot //
	
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	gPad->SetLeftMargin(0.15);
	
	histoTestStatistic->SetTitle("Test statistic");
	histoTestStatistic->GetXaxis()->SetTitle("height (cm)");
	histoTestStatistic->GetYaxis()->SetTitle("normalized no. of events");
	histoTestStatistic->SetStats(0);
	histoTestStatistic->SetLineColor(kBlue);
	histoTestStatistic->SetLineWidth(2);
	histoTestStatistic->Draw("histo");
	
	TLine *line = new TLine(dataAverage, 0.0, dataAverage, 0.01);
	line->SetLineWidth(2);
   	line->Draw();
	
	c->SaveAs("TestStatistic.png");
}

void Analyzer::Comparison(TString country, double averageCountry, double sigmaCountry)
{
	TRandom1* rand = new TRandom1();
	int N_measure = 100, N_experiment = 1000000;
	double averageSpain = 168.0, sigmaSpain = 7.0;
	double sumSpain, sumCountry;
	double pSpain, pCountry;
	double sum = 0.0, average;
	
	for(int i=0; i<N_experiment; i++)
	{
		sumSpain = 0.0;
		sumCountry = 0.0;
		for(int j=0; j<N_measure; j++)
		{
			sumSpain += rand->Gaus(averageSpain,sigmaSpain);
			sumCountry += rand->Gaus(averageCountry,sigmaCountry);
		}
		histoSpain->Fill(sumSpain/N_measure);
		histoCountry->Fill(sumCountry/N_measure);
		sum += sumCountry/N_measure;
	}
	
	average = sum/N_experiment;
	
	histoSpain->Scale(1/histoSpain->Integral());
   	histoCountry->Scale(1/histoCountry->Integral());
   	
   	if(average > averageSpain)
	{
		pSpain = histoSpain->Integral(histoSpain->FindBin(average),500);
		pCountry = histoCountry->Integral(histoCountry->FindBin(average),500);
		cout << "p(Spain) = " << pSpain << endl;
		cout << "p("+country+") = " << pCountry << endl;
	}
	else
	{
		pSpain = histoSpain->Integral(0, histoSpain->FindBin(average));
		pCountry = histoCountry->Integral(0, histoCountry->FindBin(average));
		cout << "p(Spain) = " << pSpain << endl;
		cout << "p("+country+") = " << pCountry << endl;
	}
    
	// plot //
    
	TCanvas *c = new TCanvas("c","c",1600,900);
	gPad->SetLeftMargin(0.15);
	
	histoSpain->SetTitle("Spain vs " + country);
	histoSpain->GetXaxis()->SetTitle("height (cm)");
	histoSpain->GetYaxis()->SetTitle("");
	histoSpain->SetStats(0);
	histoSpain->SetLineColor(kRed);
	histoCountry->SetLineColor(kBlue);
	histoSpain->Draw("histo");
	histoCountry->Draw("histo same");
	
	TLine *line = new TLine(average, 0.0, average, 0.03);
	line->Draw();
	
	TLegend *legend=new TLegend(0.8,0.8,0.9,0.9);
	legend->AddEntry(histoSpain, "Spain", "f");
	legend->AddEntry(histoCountry, country, "f");
	legend->Draw();
	
	c->SaveAs("Spain"+country+".png");
}










