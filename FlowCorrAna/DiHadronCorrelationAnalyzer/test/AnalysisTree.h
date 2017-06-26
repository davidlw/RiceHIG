//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 22 18:31:18 2017 by ROOT version 6.06/01
// from TTree AnalysisTree/MBUE Analysis Tree
// found on file: icm_mod14_run10.root
//////////////////////////////////////////////////////////

#ifndef AnalysisTree_h
#define AnalysisTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <vector>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"

class AnalysisTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventKind;
   TClonesArray    *MonteCarlo;
   Int_t           fNparticle;
   Int_t           fCharge[10000];   //[fNparticle]
   TH1D* hach;
   TH1D* hphiplus[100];
   TH1D* hphiminus[100];
   vector<double> achmin = {-1.,-0.1,-0.03,-0.01,0.01,0.03,0.1};
   vector<double> achmax = {-0.1,-0.03,-0.01,0.01,0.03,0.1,1.0}; 

   // List of branches
   TBranch        *b_EventKind;   //!
   TBranch        *b_MonteCarlo;   //!
   TBranch        *b_fNparticle;   //!
   TBranch        *b_fCharge;   //!

   AnalysisTree(TTree *tree=0);
   virtual ~AnalysisTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalysisTree_cxx
AnalysisTree::AnalysisTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("icm_mod15_mult300_run20.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("icm_mod15_mult300_run20.root");
      }
      f->GetObject("AnalysisTree",tree);

   }
   Init(tree);
   hach = new TH1D("hach",";A_{ch}",1001,-1-1./1000,1+1./1000);
   for(int i=0;i<(int)achmin.size();i++) 
   {
     hphiplus[i] = new TH1D(Form("hphiplus_%d",i),";#phi",32,-3.1416,3.1416);
     hphiminus[i] = new TH1D(Form("hphiminus_%d",i),";#phi",32,-3.1416,3.1416);
     hphiplus[i]->SetMarkerStyle(20);
     hphiplus[i]->SetMarkerColor(2); 
     hphiminus[i]->SetMarkerStyle(20);
     hphiminus[i]->SetMarkerColor(4); 
   }
}

AnalysisTree::~AnalysisTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalysisTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalysisTree::LoadTree(Long64_t entry)
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

void AnalysisTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   MonteCarlo = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventKind", &EventKind, &b_EventKind);
   fChain->SetBranchAddress("MonteCarlo", &MonteCarlo, &b_MonteCarlo);
   fChain->SetBranchAddress("fNparticle", &fNparticle, &b_fNparticle);
   fChain->SetBranchAddress("fCharge", fCharge, &b_fCharge);
   Notify();
}

Bool_t AnalysisTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalysisTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalysisTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AnalysisTree_cxx
