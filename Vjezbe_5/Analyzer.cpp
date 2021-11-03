#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
void Analyzer::PlotHistogram()
{
	TH1F* histo = new TH1F("histo", "pt", 100, 0, 150);
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		histo->Fill(pt1);
	}
   
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	
	histo->SetTitle(TString("Transversal momentum of decay particle 1"));
	histo->GetXaxis()->SetTitle("pt1 (GeV/c)");
	histo->GetYaxis()->SetTitle("N");
	histo->SetLineColor(2);
	histo->SetFillColor(2);
	histo->SetStats(0);
	histo->Draw();
	
	TLegend *legend= new TLegend(0.7,0.7,0.9,0.8);
	
	legend->SetHeader("Legend","C");
	legend->AddEntry(histo,"Simulated pt1","l");
	legend->Draw("pt1");
	
	c->SaveAs("pt1.pdf");
	c->SaveAs("pt1.png");
	c->SaveAs("pt1.root");
}
