#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TCanvas.h>

void Analyzer::PlotHistogram()
{	
	TFile* fw = new TFile("/home/public/data/ElectronTraining/train.root"); 
	
	if (fChain == 0)
		return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<100000;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		
		histo_ele_pt->Fill(ele_pt);
		histo_2D->Fill(ele_pt, scl_eta);
		histo_ele_ep->Fill(ele_ep);
		histo_ele_eelepout->Fill(ele_eelepout);
	}	
}

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "multipads", 3000, 900);
	c->Divide(3);
	
	gPad->SetLeftMargin(0.3);
	gPad->SetRightMargin(0.3);
	
	c->cd(1);		// ele_pt
	
	histo_ele_pt->SetTitle("Transversal momentum of electron");
	histo_ele_pt->GetXaxis()->SetTitle("p_{t}");
	histo_ele_pt->GetYaxis()->SetTitle("Events / 1");
	histo_ele_pt->SetStats(0);
	histo_ele_pt->SetLineColor(kRed);
	histo_ele_pt->SetLineWidth(3);
	histo_ele_pt->Draw("hist");
	
	c->cd(2);		// 2D ele_pt vs scl_eta
	
	histo_2D->SetTitle("ele_pt vs scl_eta");
	histo_2D->GetXaxis()->SetTitle("p_{t}");
	histo_2D->GetYaxis()->SetTitle("scl_eta");
	histo_2D->SetMinimum(-0.01);
	histo_2D->SetStats(0);
	histo_2D->Draw("COLZ");
	
	c->cd(3);		// ele_ep and ele_eelepout
	
	histo_ele_ep->SetTitle("ele_ep and ele_eelepout");
	histo_ele_ep->Scale(1.0/histo_ele_ep->Integral());
	histo_ele_ep->GetXaxis()->SetTitle("ele_ep");
	histo_ele_ep->GetYaxis()->SetTitle("Events / 0.2");
	histo_ele_ep->SetStats(0);
	histo_ele_ep->SetLineColor(kBlue);
	histo_ele_ep->SetFillColor(kBlue);
	histo_ele_ep->Draw("hist");
											
	histo_ele_eelepout->Scale(1.0/histo_ele_eelepout->Integral());
	histo_ele_eelepout->GetXaxis()->SetTitle("ele_eelepout");
	histo_ele_eelepout->SetStats(0);
	histo_ele_eelepout->SetLineColor(kRed);
	histo_ele_eelepout->SetLineWidth(3);
	histo_ele_eelepout->SetLineStyle(2);
	histo_ele_eelepout->Draw("hist same");
	
	TLegend* legend = new TLegend(0.7,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histo_ele_ep,"ele_ep","f");
	legend->AddEntry(histo_ele_eelepout,"ele_eelepout","l");
	legend->Draw();
	
	c->SaveAs("Histograms.png");
}

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
