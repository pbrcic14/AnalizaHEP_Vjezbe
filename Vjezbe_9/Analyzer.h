//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec  8 11:57:54 2021 by ROOT version 6.24/06
// from TTree Tree/Lifetime decay data
// found on file: /home/public/data/Lifetime/Lifetime.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TMath.h>

// Header file for the classes stored in the TTree if any.

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         t;

   // List of branches
   TBranch        *b_t;   //!

   TF1 *func;
   TF1 *func2;
   TF1 *func4;
   TH1F * histo;

   int N;
   double tSum;

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   virtual void PlotHistogram(TString name);
   virtual void Drawing();
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/Lifetime/Lifetime.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/Lifetime/Lifetime.root");
      }
      f->GetObject("Tree",tree);

   }
   Init(tree);
*/

   func = new TF1("func", "[0]*exp(-x/[1])/[1]" ,0.0, 10.0);
   func->SetParNames("N_{0}","#tau");
   func->SetParameters(100,1);
   func2 = new TF1("func2", "94.97*exp(-1/x)/x" ,0.0, 10.0);
   func4 = new TF1("func4", "2*([0]*TMath::Log(x)+[1]/x)" ,1.1, 1.4);
   func4->SetParNames("nentries","tSum");
   histo = new TH1F("Decay", "Decay", 100, 0.0, 10.0);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("t", &t, &b_t);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyzer_cxx
