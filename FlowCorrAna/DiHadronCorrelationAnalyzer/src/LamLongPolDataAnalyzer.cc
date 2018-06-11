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
  DiHadronCorrelationMultiBaseNew(iConfig)
{}

LamLongPolDataAnalyzer::~LamLongPolDataAnalyzer()
{}

void LamLongPolDataAnalyzer::beginJob()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {  
    for(int i=0;i<4;i++) hLongPol[itrg][i] = theOutputs->make<TH2D>(Form("cos1p_%d_trg%d",i,itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolFull[itrg] = theOutputs->make<TH2D>(Form("cos1p_trg%d",itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolFull_pos[itrg] = theOutputs->make<TH2D>(Form("cos1p_pos_trg%d",itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolFull_neg[itrg] = theOutputs->make<TH2D>(Form("cos1p_neg_trg%d",itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolPerpFull[itrg] = theOutputs->make<TH2D>(Form("cos1p_perp_trg%d",itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolPerpFull_pos[itrg] = theOutputs->make<TH2D>(Form("cos1p_perp_pos_trg%d",itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolPerpFull_neg[itrg] = theOutputs->make<TH2D>(Form("cos1p_perp_neg_trg%d",itrg),";cos(#theta_{p}^{*});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolCos2[itrg] = theOutputs->make<TH2D>(Form("cos1pcosEP2_trg%d",itrg),";cos(#theta_{p}^{*})cos(2#Delta#phi_{EP});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolSin2[itrg] = theOutputs->make<TH2D>(Form("cos1psinEP2_trg%d",itrg),";cos(#theta_{p}^{*})sin(2#Delta#phi_{EP});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolCos3[itrg] = theOutputs->make<TH2D>(Form("cos1pcosEP3_trg%d",itrg),";cos(#theta_{p}^{*})cos(3#Delta#phi_{EP});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hLongPolSin3[itrg] = theOutputs->make<TH2D>(Form("cos1psinEP3_trg%d",itrg),";cos(#theta_{p}^{*})sin(3#Delta#phi_{EP});m", 1000, -1, 1, 150, 1.115-0.0005*75, 1.115+0.0005*75);

    hdPhiEP2[itrg] = theOutputs->make<TH2D>(Form("dPhiEP2_trg%d",itrg),";dPhi_EP2;m", 36, -PI, PI, 150, 1.115-0.0005*75, 1.115+0.0005*75);
    hdPhiEP3[itrg] = theOutputs->make<TH2D>(Form("dPhiEP3_trg%d",itrg),";dPhi_EP3;m", 36, -PI, PI, 150, 1.115-0.0005*75, 1.115+0.0005*75);
  }

  hcos2_2p_ref = theOutputs->make<TH1D>("cos2_2p_ref",";cos(2#phi_{1}-2#phi_{2})", 1000, -1, 1);
  hsin2_2p_ref = theOutputs->make<TH1D>("sin2_2p_ref",";sin(2#phi_{1}-2#phi_{2})", 1000, -1, 1);
  hcos2_1p_ref = theOutputs->make<TH1D>("cos2_1p_ref",";cos(2#phi_{1})", 1000, -1, 1);
  hsin2_1p_ref = theOutputs->make<TH1D>("sin2_1p_ref",";sin(2#phi_{1})", 1000, -1, 1);
  hcos2_1p_p_ref = theOutputs->make<TH1D>("cos2_1p_p_ref",";cos(2#phi_{1})", 1000, -1, 1);
  hsin2_1p_p_ref = theOutputs->make<TH1D>("sin2_1p_p_ref",";sin(2#phi_{1})", 1000, -1, 1);
  hcos2_1p_m_ref = theOutputs->make<TH1D>("cos2_1p_m_ref",";cos(2#phi_{1})", 1000, -1, 1);
  hsin2_1p_m_ref = theOutputs->make<TH1D>("sin2_1p_m_ref",";sin(2#phi_{1})", 1000, -1, 1);

  hcos3_2p_ref = theOutputs->make<TH1D>("cos3_2p_ref",";cos(3#phi_{1}-3#phi_{2})", 1000, -1, 1);
  hsin3_2p_ref = theOutputs->make<TH1D>("sin3_2p_ref",";sin(3#phi_{1}-3#phi_{2})", 1000, -1, 1);
  hcos3_1p_ref = theOutputs->make<TH1D>("cos3_1p_ref",";cos(3#phi_{1})", 1000, -1, 1);
  hsin3_1p_ref = theOutputs->make<TH1D>("sin3_1p_ref",";sin(3#phi_{1})", 1000, -1, 1);
  hcos3_1p_p_ref = theOutputs->make<TH1D>("cos3_1p_p_ref",";cos(3#phi_{1})", 1000, -1, 1);
  hsin3_1p_p_ref = theOutputs->make<TH1D>("sin3_1p_p_ref",";sin(3#phi_{1})", 1000, -1, 1);
  hcos3_1p_m_ref = theOutputs->make<TH1D>("cos3_1p_m_ref",";cos(3#phi_{1})", 1000, -1, 1);
  hsin3_1p_m_ref = theOutputs->make<TH1D>("sin3_1p_m_ref",";sin(3#phi_{1})", 1000, -1, 1);

  DiHadronCorrelationMultiBaseNew::beginJob();
}

void LamLongPolDataAnalyzer::endJob()
{
/*
  DiHadronCorrelationMultiBaseNew::endJob();

  cout<< "Total of " << eventcorrArray.size() << " events are selected!" << endl;   
  cout<< "Start running lambda polarization analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);
  }
  cout<< "Finish running lambda polarization analysis!" << endl;
*/
}

void LamLongPolDataAnalyzer::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{
  double sin2sum_ass = 0;
  double cos2sum_ass = 0;
  double sin3sum_ass = 0;
  double cos3sum_ass = 0;
  double npair_ass = 0;
  double npair2_ass = 0;
  double sin2sum_p_ass = 0;
  double cos2sum_p_ass = 0;
  double sin3sum_p_ass = 0;
  double cos3sum_p_ass = 0;
  double npair_p_ass = 0;
  double npair2_p_ass = 0;
  double sin2sum_m_ass = 0;
  double cos2sum_m_ass = 0;
  double sin3sum_m_ass = 0;
  double cos3sum_m_ass = 0;
  double npair_m_ass = 0;
  double npair2_m_ass = 0;
  unsigned int nasssize = eventcorr.pVect_ass[0].size();
  for(unsigned int nass=0;nass<nasssize;nass++)
  {
    TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];
    double effweight_ass = (eventcorr.effVect_ass[0])[nass];
    double phi_ass = pvector_ass.Phi();
    double eta_ass = pvector_ass.Eta();

    sin2sum_ass += 1.0/effweight_ass*TMath::Sin(2*phi_ass);
    cos2sum_ass += 1.0/effweight_ass*TMath::Cos(2*phi_ass);
    sin3sum_ass += 1.0/effweight_ass*TMath::Sin(3*phi_ass);
    cos3sum_ass += 1.0/effweight_ass*TMath::Cos(3*phi_ass);

    npair_ass += 1.0/effweight_ass;
    npair2_ass += 1.0/effweight_ass/effweight_ass;

    if(eta_ass>0)
    {
      sin2sum_p_ass += 1.0/effweight_ass*TMath::Sin(2*phi_ass);
      cos2sum_p_ass += 1.0/effweight_ass*TMath::Cos(2*phi_ass);
      sin3sum_p_ass += 1.0/effweight_ass*TMath::Sin(3*phi_ass);
      cos3sum_p_ass += 1.0/effweight_ass*TMath::Cos(3*phi_ass);

      npair_p_ass += 1.0/effweight_ass;
      npair2_p_ass += 1.0/effweight_ass/effweight_ass;
    }

    if(eta_ass<0)
    {
      sin2sum_m_ass += 1.0/effweight_ass*TMath::Sin(2*phi_ass);
      cos2sum_m_ass += 1.0/effweight_ass*TMath::Cos(2*phi_ass);
      sin3sum_m_ass += 1.0/effweight_ass*TMath::Sin(3*phi_ass);
      cos3sum_m_ass += 1.0/effweight_ass*TMath::Cos(3*phi_ass);

      npair_m_ass += 1.0/effweight_ass;
      npair2_m_ass += 1.0/effweight_ass/effweight_ass;
    }
  }

  TComplex q2ass(cos2sum_ass,sin2sum_ass,0);
  TComplex q2ass_p(cos2sum_p_ass,sin2sum_p_ass,0);
  TComplex q2ass_m(cos2sum_m_ass,sin2sum_m_ass,0);
  TComplex q3ass(cos3sum_ass,sin3sum_ass,0);
  TComplex q3ass_p(cos3sum_p_ass,sin3sum_p_ass,0);
  TComplex q3ass_m(cos3sum_m_ass,sin3sum_m_ass,0);

  double cos2_2p_pm_ref = (q2ass_p*TComplex::Conjugate(q2ass_m)).Re();
  double sin2_2p_pm_ref = (q2ass_p*TComplex::Conjugate(q2ass_m)).Im();
  double cos3_2p_pm_ref = (q3ass_p*TComplex::Conjugate(q3ass_m)).Re();
  double sin3_2p_pm_ref = (q3ass_p*TComplex::Conjugate(q3ass_m)).Im();

  hcos2_1p_ref->Fill(cos2sum_ass/npair_ass,npair_ass);
  hsin2_1p_ref->Fill(sin2sum_ass/npair_ass,npair_ass);
  hcos2_1p_p_ref->Fill(cos2sum_p_ass/npair_p_ass,npair_p_ass);
  hsin2_1p_p_ref->Fill(sin2sum_p_ass/npair_p_ass,npair_p_ass);
  hcos2_1p_m_ref->Fill(cos2sum_m_ass/npair_m_ass,npair_m_ass);
  hsin2_1p_m_ref->Fill(sin2sum_m_ass/npair_m_ass,npair_m_ass);

  hcos3_1p_ref->Fill(cos3sum_ass/npair_ass,npair_ass);
  hsin3_1p_ref->Fill(sin3sum_ass/npair_ass,npair_ass);
  hcos3_1p_p_ref->Fill(cos3sum_p_ass/npair_p_ass,npair_p_ass);
  hsin3_1p_p_ref->Fill(sin3sum_p_ass/npair_p_ass,npair_p_ass);
  hcos3_1p_m_ref->Fill(cos3sum_m_ass/npair_m_ass,npair_m_ass);
  hsin3_1p_m_ref->Fill(sin3sum_m_ass/npair_m_ass,npair_m_ass);

  if(npair_p_ass && npair_m_ass)
  {
    hcos2_2p_ref->Fill(cos2_2p_pm_ref/npair_p_ass/npair_m_ass,npair_p_ass*npair_m_ass);
    hsin2_2p_ref->Fill(sin2_2p_pm_ref/npair_p_ass/npair_m_ass,npair_p_ass*npair_m_ass);

    hcos3_2p_ref->Fill(cos3_2p_pm_ref/npair_p_ass/npair_m_ass,npair_p_ass*npair_m_ass);
    hsin3_2p_ref->Fill(sin3_2p_pm_ref/npair_p_ass/npair_m_ass,npair_p_ass*npair_m_ass);
  }

  TVector3 vect2ass(cos2sum_ass,sin2sum_ass,0);
  TVector3 vect2ass_p(cos2sum_p_ass,sin2sum_p_ass,0);
  TVector3 vect2ass_m(cos2sum_m_ass,sin2sum_m_ass,0);

  TVector3 vect3ass(cos3sum_ass,sin3sum_ass,0);
  TVector3 vect3ass_p(cos3sum_p_ass,sin3sum_p_ass,0);
  TVector3 vect3ass_m(cos3sum_m_ass,sin3sum_m_ass,0);

  TVector3 vect3_beam(0,0,1);
  
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg1 = (eventcorr.pVect_trg[itrg])[ntrg];	  
      double effweight_trg1 = (eventcorr.effVect_trg[itrg])[ntrg];
      double dPhi_EP2 = pvector_trg1.Vect().DeltaPhi(vect2ass);
      double dPhi_EP3 = pvector_trg1.Vect().DeltaPhi(vect3ass);

      double y_trg1 = pvector_trg1.Rapidity() - cutPara.etacms;
/*
        double eta_trg1 = pvector_trg1.Eta();
        double phi_trg1 = pvector_trg1.Phi();
        double pt_trg1 = pvector_trg1.Pt();
*/
      double mass_trg1 = pvector_trg1.M();
        
      TVector3 ptvector_trg1 = pvector_trg1.Vect().Unit();
      ptvector_trg1.SetZ(0);
      TVector3 vect3_phi = vect3_beam.Cross(ptvector_trg1); 

      hdPhiEP2[itrg]->Fill(dPhi_EP2,mass_trg1,effweight_trg1);
      hdPhiEP3[itrg]->Fill(dPhi_EP3,mass_trg1,effweight_trg1);

      TLorentzVector pvector_trg1_dau1 = (eventcorr.pVect_trg_dau1[itrg])[ntrg];
      double theta_trg1_dau1 = pvector_trg1_dau1.Theta();
      double theta_perp_trg1_dau1 = pvector_trg1_dau1.Vect().Angle(vect3_phi);

      hLongPolCos2[itrg]->Fill(TMath::Cos(theta_trg1_dau1)*TMath::Cos(2*dPhi_EP2),mass_trg1,effweight_trg1);
      hLongPolSin2[itrg]->Fill(TMath::Cos(theta_trg1_dau1)*TMath::Sin(2*dPhi_EP2),mass_trg1,effweight_trg1);
      hLongPolCos3[itrg]->Fill(TMath::Cos(theta_trg1_dau1)*TMath::Cos(3*dPhi_EP3),mass_trg1,effweight_trg1);
      hLongPolSin3[itrg]->Fill(TMath::Cos(theta_trg1_dau1)*TMath::Sin(3*dPhi_EP3),mass_trg1,effweight_trg1);

      hLongPolFull[itrg]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(y_trg1>0) hLongPolFull_pos[itrg]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(y_trg1<0) hLongPolFull_neg[itrg]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);

      hLongPolPerpFull[itrg]->Fill(TMath::Cos(theta_perp_trg1_dau1),mass_trg1,effweight_trg1);
      if(y_trg1>0) hLongPolPerpFull_pos[itrg]->Fill(TMath::Cos(theta_perp_trg1_dau1),mass_trg1,effweight_trg1);
      if(y_trg1<0) hLongPolPerpFull_neg[itrg]->Fill(TMath::Cos(theta_perp_trg1_dau1),mass_trg1,effweight_trg1);

      if(dPhi_EP2>0 && dPhi_EP2<PI/2) hLongPol[itrg][0]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(dPhi_EP2>PI/2 && dPhi_EP2<PI) hLongPol[itrg][1]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(dPhi_EP2>-PI && dPhi_EP2<-PI/2) hLongPol[itrg][2]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
      if(dPhi_EP2>-PI/2 && dPhi_EP2<0) hLongPol[itrg][3]->Fill(TMath::Cos(theta_trg1_dau1),mass_trg1,effweight_trg1);
    } 
  }
}
