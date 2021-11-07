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
      
      cout << name1 << endl;
   }
}
void Analyzer::PlotHistogram()
{
	TH1F* histo1 = new TH1F("histo1", "pt1", 100, 0, 150);
	TH1F* histo2 = new TH1F("histo2", "pt2", 100, 0, 150);
	
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		histo1->Fill(pt1);
		histo2->Fill(pt2);
	}
   
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	
	histo1->SetTitle(TString("Transversal momentum of decay particles"));
	histo1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histo1->GetYaxis()->SetTitle("no. of events");
	histo1->SetLineColor(857); // some blue
	histo1->SetFillColor(857);
	histo1->SetStats(0);
	
	histo2->SetLineColor(kRed);
	histo2->SetLineWidth(3);
	
	histo1->Draw();
	histo2->Draw("hist same");
	
	TLegend *legend= new TLegend(0.7,0.9,0.9,0.8);
	
	legend->SetHeader("Simulated for:","C");
	legend->AddEntry(histo1,"particle 1","f");
	legend->AddEntry(histo2,"particle 2","l");
	legend->Draw();
	
	c->SaveAs("pt.pdf");
	c->SaveAs("pt.png");
	c->SaveAs("pt.root");
}
