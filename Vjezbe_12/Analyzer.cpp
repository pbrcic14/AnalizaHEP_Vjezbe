#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <iostream>

// Headers for TMVA
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"

using namespace std;

void Analyzer::Loop()
{
	Init(signal);	// signal //-------------------------------------------------------------------
   
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
		
		histoS1->Fill(ele_pt);
		histoS2->Fill(scl_eta);
		histoS3->Fill(ele_hadronicOverEm);
		histoS4->Fill(ele_gsfchi2);
		histoS5->Fill(ele_fbrem);
		histoS6->Fill(ele_ep);
		histoS7->Fill(ele_eelepout);
		histoS8->Fill(ele_pfChargedHadIso);
	}
   
	Init(background);	// background //-----------------------------------------------------------
	
	if (fChain == 0) return;
	nentries = fChain->GetEntriesFast();
	nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		
		histoB1->Fill(ele_pt);
		histoB2->Fill(scl_eta);
		histoB3->Fill(ele_hadronicOverEm);
		histoB4->Fill(ele_gsfchi2);
		histoB5->Fill(ele_fbrem);
		histoB6->Fill(ele_ep);
		histoB7->Fill(ele_eelepout);
		histoB8->Fill(ele_pfChargedHadIso);
	}
}

void Analyzer::Plot()
{
	TCanvas* c = new TCanvas("c", "c", 4800, 1800);
	c->Divide(4,2);
	
	c->cd(1);			// ele_pt //----------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoB1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histoB1->GetYaxis()->SetTitle("no. of events");
	histoB1->SetStats(0);
	histoB1->SetLineColor(kBlue);
	histoB1->SetLineWidth(4);
	histoB1->Draw();
	
	histoS1->SetLineColor(kRed);
	histoS1->SetLineWidth(2);
	histoS1->Draw("hist same");
	
	c->cd(2);			// scl_eta //---------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS2->GetXaxis()->SetTitle("scl_eta");
	histoS2->GetYaxis()->SetTitle("no. of events");
	histoS2->SetStats(0);
	histoS2->SetLineColor(kRed);
	histoS2->SetLineWidth(4);
	histoS2->Draw();
	
	histoB2->SetLineColor(kBlue);
	histoB2->SetLineWidth(2);
	histoB2->Draw("hist same");
	
	c->cd(3);			// ele_hadronicOverEm //----------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS3->GetXaxis()->SetTitle("ele_hadronicOverEm");
	histoS3->GetYaxis()->SetTitle("no. of events");
	histoS3->SetStats(0);
	histoS3->SetLineColor(kRed);
	histoS3->SetLineWidth(4);
	histoS3->Draw();
	
	histoB3->SetLineColor(kBlue);
	histoB3->SetLineWidth(2);
	histoB3->Draw("hist same");
	
	c->cd(4);			// ele_gsfchi2 //-----------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS4->GetXaxis()->SetTitle("ele_gsfchi2");
	histoS4->GetYaxis()->SetTitle("no. of events");
	histoS4->SetStats(0);
	histoS4->SetLineColor(kRed);
	histoS4->SetLineWidth(4);
	histoS4->Draw();
	
	histoB4->SetLineColor(kBlue);
	histoB4->SetLineWidth(2);
	histoB4->Draw("hist same");
	
	c->cd(5);			// ele_fbrem //-------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS5->GetXaxis()->SetTitle("ele_fbrem");
	histoS5->GetYaxis()->SetTitle("no. of events");
	histoS5->SetStats(0);
	histoS5->SetLineColor(kRed);
	histoS5->SetLineWidth(4);
	histoS5->Draw();
	
	histoB5->SetLineColor(kBlue);
	histoB5->SetLineWidth(2);
	histoB5->Draw("hist same");
	
	c->cd(6);			// ele_ep //----------------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS6->GetXaxis()->SetTitle("ele_ep");
	histoS6->GetYaxis()->SetTitle("no. of events");
	histoS6->SetStats(0);
	histoS6->SetLineColor(kRed);
	histoS6->SetLineWidth(4);
	histoS6->Draw();
	
	histoB6->SetLineColor(kBlue);
	histoB6->SetLineWidth(2);
	histoB6->Draw("hist same");
	
	c->cd(7);			// ele_eelepout //----------------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS7->GetXaxis()->SetTitle("ele_eelepout");
	histoS7->GetYaxis()->SetTitle("no. of events");
	histoS7->SetStats(0);
	histoS7->SetLineColor(kRed);
	histoS7->SetLineWidth(4);
	histoS7->Draw();
	
	histoB7->SetLineColor(kBlue);
	histoB7->SetLineWidth(2);
	histoB7->Draw("hist same");
	
	c->cd(8);			// ele_pfChargedHadIso //---------------------------------------------------
	gPad->SetLeftMargin(0.15);
	
	histoS8->GetXaxis()->SetTitle("ele_pfChargedHadIso");
	histoS8->GetYaxis()->SetTitle("no. of events");
	histoS8->SetStats(0);
	histoS8->SetLineColor(kRed);
	histoS8->SetLineWidth(4);
	histoS8->Draw();
	
	histoB8->SetLineColor(kBlue);
	histoB8->SetLineWidth(2);
	histoB8->Draw("hist same");
	
	c->SaveAs("ElectronVariables.png");
}

void Analyzer::MVATraining()
{
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
   
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
   
   // Add variables //-----------------------------------------------------------------------------
   dataloader->AddVariable( "ele_pt", 'F' );
   dataloader->AddVariable( "ele_ep", 'F' );
   dataloader->AddVariable( "ele_eelepout", 'F' );
   dataloader->AddVariable( "ele_gsfchi2", 'F' );
   
   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   
   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree( signal, signalWeight );
   dataloader->AddBackgroundTree( background, backgroundWeight );
   
   // Apply additional cuts on the signal and background samples (possibly not needed)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
   
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
   
   // Chose MVA method //--------------------------------------------------------------------------
   
   //if (Use["Likelihood"])
   //factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood", "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
   
   //if (Use["BDT"])
   factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
   
   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   
   // Save the output
   outputFile->Close();
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
   delete factory;
   delete dataloader;
}

void Analyzer::MVAPlot()
{
	TFile* f = new TFile("TMVA.root");

    TGraph* sigGraph;
    TGraph* bcgGraph;
    sigGraph = (TGraph*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_S");
    bcgGraph = (TGraph*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_B");

    TH1F* efficiency;
    efficiency = (TH1F*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_effBvsS");

    TCanvas* c = new TCanvas("c", "c", 1800, 900);
    c->Divide(2);
    gStyle->SetOptStat(0);

    c->cd(1);				// results //--------------------------------------------------------
    sigGraph->SetTitle("Distribution of MVA results (BDT)");
    sigGraph->SetLineColor(kRed);
    bcgGraph->SetLineColor(kBlue);
    sigGraph->Draw();
    bcgGraph->Draw("same");

    TLegend* legend = new TLegend(0.8, 0.82, 0.95, 0.92);
    legend->AddEntry(sigGraph, "Signal", "l");
    legend->AddEntry(bcgGraph, "Background", "l");
    legend->Draw();

    c->cd(2);				// efficiency //-----------------------------------------------------
    efficiency->SetLineColor(kGreen);
    cout << "Background omission for 90% of signal electrons: " << efficiency->Interpolate(0.9) * 100.0 << "%" << endl;
    efficiency->Draw();
	
	c->SaveAs("MVA_BDT.png");
}





