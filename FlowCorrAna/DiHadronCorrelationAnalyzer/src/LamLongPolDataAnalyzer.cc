#include "../interface/LamLongPolDataAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TVector3.h>
#include <TComplex.h>
#include <vector> 
#include <iostream>
#include "Math/Vector3D.h"

using namespace std;

LamLongPolDataAnalyzer::LamLongPolDataAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{}

LamLongPolDataAnalyzer::~LamLongPolDataAnalyzer()
{}

void LamLongPolDataAnalyzer::beginJob()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {  
    for(int i=0;i<4;i++) hLongPol[itrg][i] = theOutputs->make<TH2D>(Form("cos1p_%d_trg%d",i,itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolFull[itrg] = theOutputs->make<TH2D>(Form("cos1p_trg%d",itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolCos[itrg] = theOutputs->make<TH2D>(Form("cos1pcosEP_trg%d",itrg),";cos(#theta_{p}^{*})cos(2#Delta#phi_{EP});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolSin[itrg] = theOutputs->make<TH2D>(Form("cos1psinEP_trg%d",itrg),";cos(#theta_{p}^{*})sin(2#Delta#phi_{EP});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hdPhiEP[itrg] = theOutputs->make<TH2D>(Form("dPhiEP_trg%d",itrg),";dPhi_EP;m", 36, -PI, PI, 150, 1.115-0.0005*75, 1.115+0.0005*75);
  }

  hcos2p_ref = theOutputs->make<TH1D>("cos2p_ref",";cos(2#phi_{1}-2#phi_{2})", 1000, -1, 1);
  hsin2p_ref = theOutputs->make<TH1D>("sin2p_ref",";sin(2#phi_{1}-2#phi_{2})", 1000, -1, 1);
  hcos1p_ref = theOutputs->make<TH1D>("cos1p_ref",";cos(2#phi_{1})", 1000, -1, 1);
  hsin1p_ref = theOutputs->make<TH1D>("sin1p_ref",";sin(2#phi_{1})", 1000, -1, 1);
  hcos1p_p_ref = theOutputs->make<TH1D>("cos1p_p_ref",";cos(2#phi_{1})", 1000, -1, 1);
  hsin1p_p_ref = theOutputs->make<TH1D>("sin1p_p_ref",";sin(2#phi_{1})", 1000, -1, 1);
  hcos1p_m_ref = theOutputs->make<TH1D>("cos1p_m_ref",";cos(2#phi_{1})", 1000, -1, 1);
  hsin1p_m_ref = theOutputs->make<TH1D>("sin1p_m_ref",";sin(2#phi_{1})", 1000, -1, 1);

  DiHadronCorrelationMultiBase::beginJob();
}

void LamLongPolDataAnalyzer::endJob()
{
  DiHadronCorrelationMultiBase::endJob();

  cout<< "Total of " << eventcorrArray.size() << " events are selected!" << endl;   
  cout<< "Start running lambda polarization analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);
  }
  cout<< "Finish running lambda polarization analysis!" << endl;
}

void LamLongPolDataAnalyzer::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  double sinsum_ass = 0;
  double cossum_ass = 0;
  double npair_ass = 0;
  double npair2_ass = 0;
  double sinsum_p_ass = 0;
  double cossum_p_ass = 0;
  double npair_p_ass = 0;
  double npair2_p_ass = 0;
  double sinsum_m_ass = 0;
  double cossum_m_ass = 0;
  double npair_m_ass = 0;
  double npair2_m_ass = 0;
  unsigned int nasssize = eventcorr.pVect_ass[0].size();
  for(unsigned int nass=0;nass<nasssize;nass++)
  {
    TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];
    double effweight_ass = (eventcorr.effVect_ass[0])[nass];
    double phi_ass = pvector_ass.Phi();
    double eta_ass = pvector_ass.Eta();

    sinsum_ass += 1.0/effweight_ass*TMath::Sin(2*phi_ass);
    cossum_ass += 1.0/effweight_ass*TMath::Cos(2*phi_ass);
    npair_ass += 1.0/effweight_ass;
    npair2_ass += 1.0/effweight_ass/effweight_ass;

    if(eta_ass>0)
    {
      sinsum_p_ass += 1.0/effweight_ass*TMath::Sin(2*phi_ass);
      cossum_p_ass += 1.0/effweight_ass*TMath::Cos(2*phi_ass);
      npair_p_ass += 1.0/effweight_ass;
      npair2_p_ass += 1.0/effweight_ass/effweight_ass;
    }

    if(eta_ass<0)
    {
      sinsum_m_ass += 1.0/effweight_ass*TMath::Sin(2*phi_ass);
      cossum_m_ass += 1.0/effweight_ass*TMath::Cos(2*phi_ass);
      npair_m_ass += 1.0/effweight_ass;
      npair2_m_ass += 1.0/effweight_ass/effweight_ass;
    }
  }

  TComplex q2ass(cossum_ass,sinsum_ass,0);
  TComplex q2ass_p(cossum_p_ass,sinsum_p_ass,0);
  TComplex q2ass_m(cossum_m_ass,sinsum_m_ass,0);

  double cos2p_pm_ref = (q2ass_p*TComplex::Conjugate(q2ass_m)).Re();
  double sin2p_pm_ref = (q2ass_p*TComplex::Conjugate(q2ass_m)).Im();

  hcos1p_ref->Fill(cossum_ass/npair_ass,npair_ass);
  hsin1p_ref->Fill(sinsum_ass/npair_ass,npair_ass);
  hcos1p_p_ref->Fill(cossum_p_ass/npair_p_ass,npair_p_ass);
  hsin1p_p_ref->Fill(sinsum_p_ass/npair_p_ass,npair_p_ass);
  hcos1p_m_ref->Fill(cossum_m_ass/npair_m_ass,npair_m_ass);
  hsin1p_m_ref->Fill(sinsum_m_ass/npair_m_ass,npair_m_ass);

  if(npair_p_ass && npair_m_ass)
  {
    hcos2p_ref->Fill(cos2p_pm_ref/npair_p_ass/npair_m_ass,npair_p_ass*npair_m_ass);
    hsin2p_ref->Fill(sin2p_pm_ref/npair_p_ass/npair_m_ass,npair_p_ass*npair_m_ass);
  }

  TVector3 vectass(cossum_ass,sinsum_ass,0);
  TVector3 vectass_p(cossum_p_ass,sinsum_p_ass,0);
  TVector3 vectass_m(cossum_m_ass,sinsum_m_ass,0);

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg1 = (eventcorr.pVect_trg[itrg])[ntrg];	  
      double effweight_trg1 = (eventcorr.effVect_trg[itrg])[ntrg];
      double dPhi_EP = pvector_trg1.Vect().DeltaPhi(vectass);
/*
        double eta_trg1 = pvector_trg1.Eta();
        double phi_trg1 = pvector_trg1.Phi();
        double pt_trg1 = pvector_trg1.Pt();
*/
      double mass_trg1 = pvector_trg1.M();
        
      hdPhiEP[itrg]->Fill(dPhi_EP,mass_trg1,effweight_trg1);

      TLorentzVector pvector_trg1_dau1 = (eventcorr.pVect_trg_dau1[itrg])[ntrg];
      double theta_trg1_dau1 = pvector_trg1_dau1.Theta();

      hLongPolCos[itrg]->Fill(TMath::Cos(theta_trg1_dau1)*TMath::Cos(2*dPhi_EP),mass_trg1,effweight_trg1);
      hLongPolSin[itrg]->Fill(TMath::Cos(theta_trg1_dau1)*TMath::Sin(2*dPhi_EP),mass_trg1,effweight_trg1);

      hLongPolFull[itrg]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(dPhi_EP>0 && dPhi_EP<PI/2) hLongPol[itrg][0]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(dPhi_EP>PI/2 && dPhi_EP<PI) hLongPol[itrg][1]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(dPhi_EP>-PI && dPhi_EP<-PI/2) hLongPol[itrg][2]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(dPhi_EP>-PI/2 && dPhi_EP<0) hLongPol[itrg][3]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
    } 
  }
}
