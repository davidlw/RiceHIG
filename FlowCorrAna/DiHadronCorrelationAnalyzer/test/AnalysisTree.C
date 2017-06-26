#define AnalysisTree_cxx
#include "AnalysisTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>

void AnalysisTree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L AnalysisTree.C
//      root> AnalysisTree t
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
  
      Int_t NplusTot=0;
      Int_t NminusTot=0;
      Int_t nparticle = MonteCarlo->GetEntriesFast();
      for (Int_t i=0;i<nparticle;i++) {
         TLorentzVector *pvect = (TLorentzVector*)MonteCarlo->At(i);
         Int_t charge = fCharge[i]; 
         if(fabs(pvect->Eta())>2.4) continue;
         if(charge>0) NplusTot++;
         if(charge<0) NminusTot++;
      } 
      Double_t Ach = (NminusTot - NplusTot) / (NminusTot + (Double_t)NplusTot);
      if(hach) hach->Fill((Double_t)Ach);

      for (Int_t i=0;i<nparticle;i++) {
        TLorentzVector *pvect = (TLorentzVector*)MonteCarlo->At(i);
        Int_t charge = fCharge[i]; 
        if(fabs(pvect->Eta())>2.4) continue;
        for(int jj = 0; jj<(int)achmin.size();jj++)
        {
          if(Ach>achmin[jj] && Ach<achmax[jj]) 
          {
            if(charge>0) hphiplus[jj]->Fill(pvect->Phi());
            if(charge<0) hphiminus[jj]->Fill(pvect->Phi());
          }
        }
      }
    // if (Cut(ientry) < 0) continue;
   }
   TCanvas* c = new TCanvas("c","c",500,500);
   hach->Draw();

   TCanvas* c1 = new TCanvas("c1","c1",800,400);
   c1->Divide(4,2);
   for(int i=0;i<7;i++)
   {
     c1->cd(i+1);
     hphiplus[i]->Scale(1.0/hphiplus[i]->Integral());
     hphiminus[i]->Scale(1.0/hphiminus[i]->Integral());
     hphiplus[i]->Draw("PE");
     hphiminus[i]->Draw("PESAME");
   }
}
