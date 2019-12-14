#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/RCorrelatorAnalyzer.h"
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

RCorrelatorAnalyzer::RCorrelatorAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{}

//RCorrelatorAnalyzer::~RCorrelatorAnalyzer()
//{}

//
// member functions
//

void RCorrelatorAnalyzer::beginJob()
{
  hAch = theOutputs->make<TH1D>("hAch",";A_{ch}",200,-1,1);

  hEtaPhi_pos = theOutputs->make<TH2D>("dNdetadphi_weight_pos",";#eta;#phi",96,-2.4,2.4,72,-PI,PI);
  hEtaPhi_neg = theOutputs->make<TH2D>("dNdetadphi_weight_neg",";#eta;#phi",96,-2.4,2.4,72,-PI,PI);

  hNreal2_p = theOutputs->make<TH1D>("hNreal2_p",";#DeltaS",400,-2,2);
  hNreal2_m = theOutputs->make<TH1D>("hNreal2_m",";#DeltaS",400,-2,2);
  hNreal3_p = theOutputs->make<TH1D>("hNreal3_p",";#DeltaS",400,-2,2);
  hNreal3_m = theOutputs->make<TH1D>("hNreal3_m",";#DeltaS",400,-2,2);
  hNreal2perp_p = theOutputs->make<TH1D>("hNreal2perp_p",";#DeltaS",400,-2,2);
  hNreal2perp_m = theOutputs->make<TH1D>("hNreal2perp_m",";#DeltaS",400,-2,2);
  hNreal3perp_p = theOutputs->make<TH1D>("hNreal3perp_p",";#DeltaS",400,-2,2);
  hNreal3perp_m = theOutputs->make<TH1D>("hNreal3perp_m",";#DeltaS",400,-2,2);

  hNshuffle2_p = theOutputs->make<TH1D>("hNshuffle2_p",";#DeltaS",400,-2,2);
  hNshuffle2_m = theOutputs->make<TH1D>("hNshuffle2_m",";#DeltaS",400,-2,2);
  hNshuffle3_p = theOutputs->make<TH1D>("hNshuffle3_p",";#DeltaS",400,-2,2);
  hNshuffle3_m = theOutputs->make<TH1D>("hNshuffle3_m",";#DeltaS",400,-2,2);
  hNshuffle2perp_p = theOutputs->make<TH1D>("hNshuffle2perp_p",";#DeltaS",400,-2,2);
  hNshuffle2perp_m = theOutputs->make<TH1D>("hNshuffle2perp_m",";#DeltaS",400,-2,2);
  hNshuffle3perp_p = theOutputs->make<TH1D>("hNshuffle3perp_p",";#DeltaS",400,-2,2);
  hNshuffle3perp_m = theOutputs->make<TH1D>("hNshuffle3perp_m",";#DeltaS",400,-2,2);

  hAbsNreal2_p = theOutputs->make<TH1D>("hAbsNreal2_p",";|#DeltaS|",400,-2,2);
  hAbsNreal2_m = theOutputs->make<TH1D>("hAbsNreal2_m",";|#DeltaS|",400,-2,2);
  hAbsNreal3_p = theOutputs->make<TH1D>("hAbsNreal3_p",";|#DeltaS|",400,-2,2);
  hAbsNreal3_m = theOutputs->make<TH1D>("hAbsNreal3_m",";|#DeltaS|",400,-2,2);
  hAbsNreal2perp_p = theOutputs->make<TH1D>("hAbsNreal2perp_p",";|#DeltaS|",400,-2,2);
  hAbsNreal2perp_m = theOutputs->make<TH1D>("hAbsNreal2perp_m",";|#DeltaS|",400,-2,2);
  hAbsNreal3perp_p = theOutputs->make<TH1D>("hAbsNreal3perp_p",";|#DeltaS|",400,-2,2);
  hAbsNreal3perp_m = theOutputs->make<TH1D>("hAbsNreal3perp_m",";|#DeltaS|",400,-2,2);
  
  hAbsNshuffle2_p = theOutputs->make<TH1D>("hAbsNshuffle2_p",";|#DeltaS|",400,-2,2);
  hAbsNshuffle2_m = theOutputs->make<TH1D>("hAbsNshuffle2_m",";|#DeltaS|",400,-2,2);
  hAbsNshuffle3_p = theOutputs->make<TH1D>("hAbsNshuffle3_p",";|#DeltaS|",400,-2,2);
  hAbsNshuffle3_m = theOutputs->make<TH1D>("hAbsNshuffle3_m",";|#DeltaS|",400,-2,2);
  hAbsNshuffle2perp_p = theOutputs->make<TH1D>("hAbsNshuffle2perp_p",";|#DeltaS|",400,-2,2);
  hAbsNshuffle2perp_m = theOutputs->make<TH1D>("hAbsNshuffle2perp_m",";|#DeltaS|",400,-2,2);
  hAbsNshuffle3perp_p = theOutputs->make<TH1D>("hAbsNshuffle3perp_p",";|#DeltaS|",400,-2,2);
  hAbsNshuffle3perp_m = theOutputs->make<TH1D>("hAbsNshuffle3perp_m",";|#DeltaS|",400,-2,2);

  hR2_p = theOutputs->make<TH1D>("hR2_p",";#DeltaS",400,-2,2);
  hR2_m = theOutputs->make<TH1D>("hR2_m",";#DeltaS",400,-2,2);
  hR3_p = theOutputs->make<TH1D>("hR3_p",";#DeltaS",400,-2,2);
  hR3_m = theOutputs->make<TH1D>("hR3_m",";#DeltaS",400,-2,2);

  hAbsR2_p = theOutputs->make<TH1D>("hAbsR2_p",";|#DeltaS|",400,-2,2);
  hAbsR2_m = theOutputs->make<TH1D>("hAbsR2_m",";|#DeltaS|",400,-2,2);
  hAbsR3_p = theOutputs->make<TH1D>("hAbsR3_p",";|#DeltaS|",400,-2,2);
  hAbsR3_m = theOutputs->make<TH1D>("hAbsR3_m",";|#DeltaS|",400,-2,2);

  hPairCosnAss = theOutputs->make<TH2D>("paircosn_ass",";cos(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hPairSinnAss = theOutputs->make<TH2D>("pairsinn_ass",";sin(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hCosnAss_hfp = theOutputs->make<TH2D>("cosn_hfp_ass",";cos(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hSinnAss_hfp = theOutputs->make<TH2D>("sinn_hfp_ass",";sin(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hCosnAss_hfm = theOutputs->make<TH2D>("cosn_hfm_ass",";cos(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hSinnAss_hfm = theOutputs->make<TH2D>("sinn_hfm_ass",";sin(n#phi);n",10,-1.0,1.0,5,0.5,5.5);

  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------
/*
void RCorrelatorAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  DiHadronCorrelationMultiBaseNew::analyze(iEvent,iSetup);

  FillHistsSignal(*eventcorr);
}
*/

void RCorrelatorAnalyzer::endJob()
{
  hR2_p->Add(hNreal2_p);
  hR2_p->Divide(hNshuffle2_p);
  hR2_p->Divide(hNreal2perp_p);
  hR2_p->Multiply(hNshuffle2perp_p);

  hR2_m->Add(hNreal2_m);
  hR2_m->Divide(hNshuffle2_m);
  hR2_m->Divide(hNreal2perp_m);
  hR2_m->Multiply(hNshuffle2perp_m);

  hR3_p->Add(hNreal3_p);
  hR3_p->Divide(hNshuffle3_p);
  hR3_p->Divide(hNreal3perp_p);
  hR3_p->Multiply(hNshuffle3perp_p);

  hR3_m->Add(hNreal3_m);
  hR3_m->Divide(hNshuffle3_m);
  hR3_m->Divide(hNreal3perp_m);
  hR3_m->Multiply(hNshuffle3perp_m);

  hAbsR2_p->Add(hAbsNreal2_p);
  hAbsR2_p->Divide(hAbsNshuffle2_p);
  hAbsR2_p->Divide(hAbsNreal2perp_p);
  hAbsR2_p->Multiply(hAbsNshuffle2perp_p);

  hAbsR2_m->Add(hAbsNreal2_m);
  hAbsR2_m->Divide(hAbsNshuffle2_m);
  hAbsR2_m->Divide(hAbsNreal2perp_m);
  hAbsR2_m->Multiply(hAbsNshuffle2perp_m);

  hAbsR3_p->Add(hAbsNreal3_p);
  hAbsR3_p->Divide(hAbsNshuffle3_p);
  hAbsR3_p->Divide(hAbsNreal3perp_p);
  hAbsR3_p->Multiply(hAbsNshuffle3perp_p);

  hAbsR3_m->Add(hAbsNreal3_m);
  hAbsR3_m->Divide(hAbsNshuffle3_m);
  hAbsR3_m->Divide(hAbsNreal3perp_m);
  hAbsR3_m->Multiply(hAbsNshuffle3perp_m);
}

void RCorrelatorAnalyzer::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{
   double sumcosn_p_ass[5]={0.0};
   double sumsinn_p_ass[5]={0.0};
   double npairs_p_ass[5]={0.0};
   double sumcosn_m_ass[5]={0.0};
   double sumsinn_m_ass[5]={0.0};
   double npairs_m_ass[5]={0.0};

   unsigned int nasssize = eventcorr.pVect_ass[0].size();
   for(unsigned int nass=0;nass<nasssize;nass++)
   {
     TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];

     double effweight_ass = (eventcorr.effVect_ass[0])[nass];
     double eta_ass = pvector_ass.Eta()-cutPara.etacms;
     double phi_ass = pvector_ass.Phi();

     for(int nn = 0; nn<5; nn++)
     {
       if(eta_ass>0.0)
       {
         sumcosn_p_ass[nn] = sumcosn_p_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
         sumsinn_p_ass[nn] = sumsinn_p_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
         npairs_p_ass[nn] += 1.0/effweight_ass;
       }
       else if(nn==0) 
       {
         sumcosn_m_ass[nn] = sumcosn_m_ass[nn] - cos((nn+1)*phi_ass)/effweight_ass;
         sumsinn_m_ass[nn] = sumsinn_m_ass[nn] - sin((nn+1)*phi_ass)/effweight_ass;
         npairs_m_ass[nn] += 1.0/effweight_ass;
       }
       else
       {
         sumcosn_m_ass[nn] = sumcosn_m_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
         sumsinn_m_ass[nn] = sumsinn_m_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
         npairs_m_ass[nn] += 1.0/effweight_ass;
       }
     }
   }
   
   for(int nn = 0; nn<5; nn++)
   {
     hCosnAss_hfp->Fill(sumcosn_p_ass[nn]/npairs_p_ass[nn],nn+1,npairs_p_ass[nn]);
     hSinnAss_hfp->Fill(sumsinn_p_ass[nn]/npairs_p_ass[nn],nn+1,npairs_p_ass[nn]);
     hCosnAss_hfm->Fill(sumcosn_m_ass[nn]/npairs_m_ass[nn],nn+1,npairs_m_ass[nn]);
     hSinnAss_hfm->Fill(sumsinn_m_ass[nn]/npairs_m_ass[nn],nn+1,npairs_m_ass[nn]);

     double Qx2 = sumcosn_m_ass[nn]*sumcosn_p_ass[nn]+sumsinn_m_ass[nn]*sumsinn_p_ass[nn];
     double Qy2 = -sumcosn_m_ass[nn]*sumsinn_p_ass[nn]+sumsinn_m_ass[nn]*sumcosn_p_ass[nn];
     hPairCosnAss->Fill(Qx2/npairs_m_ass[nn]/npairs_p_ass[nn],nn+1,npairs_m_ass[nn]*npairs_p_ass[nn]);
     hPairSinnAss->Fill(Qy2/npairs_m_ass[nn]/npairs_p_ass[nn],nn+1,npairs_m_ass[nn]*npairs_p_ass[nn]);
   }

   TVector2 ep2_p(sumcosn_p_ass[1]/npairs_p_ass[1],sumsinn_p_ass[1]/npairs_p_ass[1]);
   TVector2 ep2_m(sumcosn_m_ass[1]/npairs_m_ass[1],sumsinn_m_ass[1]/npairs_m_ass[1]);
   TVector2 ep3_p(sumcosn_p_ass[2]/npairs_p_ass[2],sumsinn_p_ass[2]/npairs_p_ass[2]);
   TVector2 ep3_m(sumcosn_m_ass[2]/npairs_m_ass[2],sumsinn_m_ass[2]/npairs_m_ass[2]);
   double ep2angle_p = ep2_p.Phi()/2.;
   double ep2angle_m = ep2_m.Phi()/2.;
   double ep3angle_p = ep3_p.Phi()/3.;
   double ep3angle_m = ep3_m.Phi()/3.;

   double deltaS2_pos_p=0;
   double deltaS2_neg_p=0;
   double deltaS2_pos_m=0;
   double deltaS2_neg_m=0;
   double deltaS3_pos_p=0;
   double deltaS3_neg_p=0;
   double deltaS3_pos_m=0;
   double deltaS3_neg_m=0;
   double deltaS2perp_pos_p=0;
   double deltaS2perp_neg_p=0;
   double deltaS2perp_pos_m=0;
   double deltaS2perp_neg_m=0;
   double deltaS3perp_pos_p=0;
   double deltaS3perp_neg_p=0;
   double deltaS3perp_pos_m=0;
   double deltaS3perp_neg_m=0;
   double SdeltaS2_pos_p=0;
   double SdeltaS2_neg_p=0;
   double SdeltaS2_pos_m=0;
   double SdeltaS2_neg_m=0;
   double SdeltaS3_pos_p=0;
   double SdeltaS3_neg_p=0;
   double SdeltaS3_pos_m=0;
   double SdeltaS3_neg_m=0;
   double SdeltaS2perp_pos_p=0;
   double SdeltaS2perp_neg_p=0;
   double SdeltaS2perp_pos_m=0;
   double SdeltaS2perp_neg_m=0;
   double SdeltaS3perp_pos_p=0;
   double SdeltaS3perp_neg_p=0;
   double SdeltaS3perp_pos_m=0;
   double SdeltaS3perp_neg_m=0;

   double ntrg_pos=0;
   double ntrg_neg=0;
   double Sntrg_pos=0;
   double Sntrg_neg=0;
   unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
   for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
   {
     TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];
     double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
     double eta_trg = pvector_trg.Eta()-cutPara.etacms;
     double phi_trg = pvector_trg.Phi();
     double charge_trg = (eventcorr.chgVect_trg[0])[ntrg];

     if(charge_trg>0)
     {
       hEtaPhi_pos->Fill(eta_trg,phi_trg,1.0/effweight_trg);

       deltaS2_pos_p += sin(phi_trg-ep2angle_p)/effweight_trg;
       deltaS2_pos_m += sin(phi_trg-ep2angle_m)/effweight_trg;
       deltaS3_pos_p += sin(3./2*(phi_trg-ep3angle_p))/effweight_trg;
       deltaS3_pos_m += sin(3./2*(phi_trg-ep3angle_m))/effweight_trg;

       deltaS2perp_pos_p += sin(phi_trg-ep2angle_p-PI/2.)/effweight_trg;
       deltaS2perp_pos_m += sin(phi_trg-ep2angle_m-PI/2.)/effweight_trg;
       deltaS3perp_pos_p += sin(3./2*(phi_trg-ep3angle_p-PI/3.))/effweight_trg;
       deltaS3perp_pos_m += sin(3./2*(phi_trg-ep3angle_m-PI/3.))/effweight_trg;

       ntrg_pos += 1.0/effweight_trg;
     }
     if(charge_trg<0) 
     { 
       hEtaPhi_neg->Fill(eta_trg,phi_trg,1.0/effweight_trg);

       deltaS2_neg_p += sin(phi_trg-ep2angle_p)/effweight_trg;
       deltaS2_neg_m += sin(phi_trg-ep2angle_m)/effweight_trg;
       deltaS3_neg_p += sin(3./2*(phi_trg-ep3angle_p))/effweight_trg;
       deltaS3_neg_m += sin(3./2*(phi_trg-ep3angle_m))/effweight_trg;

       deltaS2perp_neg_p += sin(phi_trg-ep2angle_p-PI/2.)/effweight_trg;
       deltaS2perp_neg_m += sin(phi_trg-ep2angle_m-PI/2.)/effweight_trg;
       deltaS3perp_neg_p += sin(3./2*(phi_trg-ep3angle_p-PI/3.))/effweight_trg;
       deltaS3perp_neg_m += sin(3./2*(phi_trg-ep3angle_m-PI/3.))/effweight_trg;

       ntrg_neg += 1.0/effweight_trg;
     }

     double ch_ran = gRandom->Rndm()-0.5;
     if(ch_ran>0)
     { 
       SdeltaS2_pos_p += sin(phi_trg-ep2angle_p)/effweight_trg;
       SdeltaS2_pos_m += sin(phi_trg-ep2angle_m)/effweight_trg;
       SdeltaS3_pos_p += sin(3./2*(phi_trg-ep3angle_p))/effweight_trg;
       SdeltaS3_pos_m += sin(3./2*(phi_trg-ep3angle_m))/effweight_trg;
       
       SdeltaS2perp_pos_p += sin(phi_trg-ep2angle_p-PI/2.)/effweight_trg;
       SdeltaS2perp_pos_m += sin(phi_trg-ep2angle_m-PI/2.)/effweight_trg;
       SdeltaS3perp_pos_p += sin(3./2*(phi_trg-ep3angle_p-PI/3.))/effweight_trg;
       SdeltaS3perp_pos_m += sin(3./2*(phi_trg-ep3angle_m-PI/3.))/effweight_trg;
       
       Sntrg_pos += 1.0/effweight_trg;
     }
     if(ch_ran<0)
     { 
       SdeltaS2_neg_p += sin(phi_trg-ep2angle_p)/effweight_trg;
       SdeltaS2_neg_m += sin(phi_trg-ep2angle_m)/effweight_trg;
       SdeltaS3_neg_p += sin(3./2*(phi_trg-ep3angle_p))/effweight_trg;
       SdeltaS3_neg_m += sin(3./2*(phi_trg-ep3angle_m))/effweight_trg;
       
       SdeltaS2perp_neg_p += sin(phi_trg-ep2angle_p-PI/2.)/effweight_trg;
       SdeltaS2perp_neg_m += sin(phi_trg-ep2angle_m-PI/2.)/effweight_trg;
       SdeltaS3perp_neg_p += sin(3./2*(phi_trg-ep3angle_p-PI/3.))/effweight_trg;
       SdeltaS3perp_neg_m += sin(3./2*(phi_trg-ep3angle_m-PI/3.))/effweight_trg;
       
       Sntrg_neg += 1.0/effweight_trg;
     }
   }

   double ach = (ntrg_pos-ntrg_neg)/(ntrg_pos+ntrg_neg);
   hAch->Fill(ach);

   double deltaS2_p=deltaS2_pos_p/ntrg_pos-deltaS2_neg_p/ntrg_neg;
   double deltaS2_m=deltaS2_pos_m/ntrg_pos-deltaS2_neg_m/ntrg_neg;
   double deltaS3_p=deltaS3_pos_p/ntrg_pos-deltaS3_neg_p/ntrg_neg;
   double deltaS3_m=deltaS3_pos_m/ntrg_pos-deltaS3_neg_m/ntrg_neg;   
   double deltaS2perp_p=deltaS2perp_pos_p/ntrg_pos-deltaS2perp_neg_p/ntrg_neg;
   double deltaS2perp_m=deltaS2perp_pos_m/ntrg_pos-deltaS2perp_neg_m/ntrg_neg;
   double deltaS3perp_p=deltaS3perp_pos_p/ntrg_pos-deltaS3perp_neg_p/ntrg_neg;
   double deltaS3perp_m=deltaS3perp_pos_m/ntrg_pos-deltaS3perp_neg_m/ntrg_neg;

   hNreal2_p->Fill(deltaS2_p);
   hNreal2_m->Fill(deltaS2_m);
   hNreal3_p->Fill(deltaS3_p);
   hNreal3_m->Fill(deltaS3_m);
   hNreal2perp_p->Fill(deltaS2perp_p);
   hNreal2perp_m->Fill(deltaS2perp_m);
   hNreal3perp_p->Fill(deltaS3perp_p);
   hNreal3perp_m->Fill(deltaS3perp_m);

   hAbsNreal2_p->Fill(deltaS2_p);
   hAbsNreal2_m->Fill(deltaS2_m);
   hAbsNreal3_p->Fill(deltaS3_p);
   hAbsNreal3_m->Fill(deltaS3_m);
   hAbsNreal2perp_p->Fill(deltaS2perp_p);
   hAbsNreal2perp_m->Fill(deltaS2perp_m);
   hAbsNreal3perp_p->Fill(deltaS3perp_p);
   hAbsNreal3perp_m->Fill(deltaS3perp_m);
   hAbsNreal2_p->Fill(-deltaS2_p);
   hAbsNreal2_m->Fill(-deltaS2_m);
   hAbsNreal3_p->Fill(-deltaS3_p);
   hAbsNreal3_m->Fill(-deltaS3_m);
   hAbsNreal2perp_p->Fill(-deltaS2perp_p);
   hAbsNreal2perp_m->Fill(-deltaS2perp_m);
   hAbsNreal3perp_p->Fill(-deltaS3perp_p);
   hAbsNreal3perp_m->Fill(-deltaS3perp_m);

   double SdeltaS2_p=SdeltaS2_pos_p/Sntrg_pos-SdeltaS2_neg_p/Sntrg_neg;
   double SdeltaS2_m=SdeltaS2_pos_m/Sntrg_pos-SdeltaS2_neg_m/Sntrg_neg;
   double SdeltaS3_p=SdeltaS3_pos_p/Sntrg_pos-SdeltaS3_neg_p/Sntrg_neg;
   double SdeltaS3_m=SdeltaS3_pos_m/Sntrg_pos-SdeltaS3_neg_m/Sntrg_neg;
   double SdeltaS2perp_p=SdeltaS2perp_pos_p/Sntrg_pos-SdeltaS2perp_neg_p/Sntrg_neg;
   double SdeltaS2perp_m=SdeltaS2perp_pos_m/Sntrg_pos-SdeltaS2perp_neg_m/Sntrg_neg;
   double SdeltaS3perp_p=SdeltaS3perp_pos_p/Sntrg_pos-SdeltaS3perp_neg_p/Sntrg_neg;
   double SdeltaS3perp_m=SdeltaS3perp_pos_m/Sntrg_pos-SdeltaS3perp_neg_m/Sntrg_neg;

   hNshuffle2_p->Fill(SdeltaS2_p);
   hNshuffle2_m->Fill(SdeltaS2_m);
   hNshuffle3_p->Fill(SdeltaS3_p);
   hNshuffle3_m->Fill(SdeltaS3_m);
   hNshuffle2perp_p->Fill(SdeltaS2perp_p);
   hNshuffle2perp_m->Fill(SdeltaS2perp_m);
   hNshuffle3perp_p->Fill(SdeltaS3perp_p);
   hNshuffle3perp_m->Fill(SdeltaS3perp_m);

   hAbsNshuffle2_p->Fill(SdeltaS2_p);
   hAbsNshuffle2_m->Fill(SdeltaS2_m);
   hAbsNshuffle3_p->Fill(SdeltaS3_p);
   hAbsNshuffle3_m->Fill(SdeltaS3_m);
   hAbsNshuffle2perp_p->Fill(SdeltaS2perp_p);
   hAbsNshuffle2perp_m->Fill(SdeltaS2perp_m);
   hAbsNshuffle3perp_p->Fill(SdeltaS3perp_p);
   hAbsNshuffle3perp_m->Fill(SdeltaS3perp_m);
   hAbsNshuffle2_p->Fill(-SdeltaS2_p);
   hAbsNshuffle2_m->Fill(-SdeltaS2_m);
   hAbsNshuffle3_p->Fill(-SdeltaS3_p);
   hAbsNshuffle3_m->Fill(-SdeltaS3_m);
   hAbsNshuffle2perp_p->Fill(-SdeltaS2perp_p);
   hAbsNshuffle2perp_m->Fill(-SdeltaS2perp_m);
   hAbsNshuffle3perp_p->Fill(-SdeltaS3perp_p);
   hAbsNshuffle3perp_m->Fill(-SdeltaS3perp_m);
}
