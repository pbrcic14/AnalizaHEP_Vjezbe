#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

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
      
      cout << name1 << endl;
   }
}
void Analyzer::PlotHistogram()
{
	TCanvas* c = new TCanvas("c", "c", 1800, 900);
	c->Divide(2);
	
	TH1F* histo1 = new TH1F("histo1", "Transversal momentum of decay particles", 100, 0, 150);
	TH1F* histo2 = new TH1F("histo2", "Transversal momentum of decay particles", 100, 0, 150);
	TH1F* histoH = new TH1F("histoH", "Transversal momentum of reconstructed Higgs", 100, 0, 150);
	
	TLorentzVector* Higgs = new TLorentzVector();
	
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
		
		histo1->Fill(pt1);
		histo2->Fill(pt2);
		
		Higgs->SetPxPyPzE(px1+px2, py1+py2, pz1+pz2, E1+E2);
		histoH->Fill(Higgs->Pt());
	}
	
	c->cd(1);
	histo1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histo1->GetYaxis()->SetTitle("no. of events");
	histo1->SetLineColor(kBlue-4);
	histo1->SetFillColor(kBlue-4);
	histo1->SetStats(0);
	histo1->Draw();
	
	histo2->SetLineColor(kRed);
	histo2->SetLineWidth(3);
	histo2->Draw("hist same");
	
	TLegend* legend = new TLegend(0.6,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histo1,"Decay particle 1","f");
	legend->AddEntry(histo2,"Decay particle 2","l");
	legend->Draw();
	
	c->cd(2);
	histoH->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histoH->GetYaxis()->SetTitle("no. of events");
	histoH->SetLineColor(kGreen+2);
	histoH->SetFillColor(kGreen+2);
	histoH->SetStats(0);
	histoH->Draw();
	
	TLegend* legendH = new TLegend(0.1,0.8,0.45,0.9);
	legendH->SetTextSize(0.03);
	legendH->AddEntry(histoH, "Reconstructed Higgs", "f");
	legendH->Draw();	
	
	c->SaveAs("Reconstructed.pdf");
	c->SaveAs("Reconstructed.png");
	c->SaveAs("Reconstructed.root");
}
