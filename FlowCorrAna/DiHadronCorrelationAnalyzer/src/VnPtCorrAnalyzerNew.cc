#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/VnPtCorrAnalyzerNew.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TObjString.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TGenPhaseSpace.h>
#include <iostream>

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

VnPtCorrAnalyzerNew::VnPtCorrAnalyzerNew(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{}

//VnPtCorrAnalyzerNew::~VnPtCorrAnalyzerNew()
//{}

//
// member functions
//

void VnPtCorrAnalyzerNew::beginJob()
{
  hPairCosn =  theOutputs->make<TH2D>("paircosn",";n;cos(n#Delta#phi)",1000,0,1000,1000,-1.0,1.0);
  hPairCosnPt =  theOutputs->make<TH2D>("paircosnpt",";n;cos(n#Delta#phi)*p_{T}",1000,0,1000,1000,-2.0,2.0);
  hPt=  theOutputs->make<TH2D>("pt",";n;p_{T}",1000,0,1000,500,0,5);

  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------
/*
void VnPtCorrAnalyzerNew::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  DiHadronCorrelationMultiBaseNew::analyze(iEvent,iSetup);

  FillHistsSignal(*eventcorr);
}
*/

void VnPtCorrAnalyzerNew::endJob()
{}

void VnPtCorrAnalyzerNew::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{
   double sumcosn_pos[5]={0.0};
   double sumsinn_pos[5]={0.0};
   double sumcosn_neg[5]={0.0};
   double sumsinn_neg[5]={0.0};
   double npairs_pos = 0;
   double npairs_neg = 0;
   double npairs_mid = 0;
   double pt_mid = 0;

   unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
   for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
   {
     TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];
     double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
     double eta_trg = pvector_trg.Eta()-cutPara.etacms;
     double phi_trg = pvector_trg.Phi();
     double pt_trg = pvector_trg.Pt();

     if(eta_trg<-0.5 && eta_trg>-2.4)
     {
       npairs_neg += 1.0/fabs(effweight_trg);
       for(int nn = 1; nn<2; nn++)
       {
         sumcosn_neg[nn] += cos((nn+1)*phi_trg)/effweight_trg;
         sumsinn_neg[nn] += sin((nn+1)*phi_trg)/effweight_trg;
       }
     }

     if(eta_trg>0.5 && eta_trg<2.4)
     {
       npairs_pos += 1.0/fabs(effweight_trg);
       for(int nn = 1; nn<2; nn++)
       {
         sumcosn_pos[nn] += cos((nn+1)*phi_trg)/effweight_trg;
         sumsinn_pos[nn] += sin((nn+1)*phi_trg)/effweight_trg;
       }
     }

     if(eta_trg>-0.5 && eta_trg<0.5)
     {
       npairs_mid += 1.0/fabs(effweight_trg);
       pt_mid += pt_trg/fabs(effweight_trg);
     }
   }

   double Qx2 = sumcosn_pos[1]*sumcosn_neg[1]+sumsinn_pos[1]*sumsinn_neg[1];
//   double Qy2 = -sumcosn_pos[1]*sumsinn_neg[1]+sumsinn_pos[1]*sumcosn_neg[1];
   hPairCosn->Fill(npairs_pos+npairs_neg+npairs_mid,Qx2/npairs_pos/npairs_neg,npairs_pos*npairs_neg);
   hPairCosnPt->Fill(npairs_pos+npairs_neg+npairs_mid,pt_mid*Qx2/npairs_pos/npairs_neg/npairs_mid,npairs_mid*npairs_pos*npairs_neg);
   hPt->Fill(npairs_pos+npairs_neg+npairs_mid,pt_mid/npairs_mid,npairs_mid);
}
