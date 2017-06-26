#include "../interface/LamPolGenAnalyzer.h"
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
#include <vector> 
#include <iostream>
#include "Math/Vector3D.h"

using namespace std;

LamPolGenAnalyzer::LamPolGenAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  cutPara.IsBoostRestFrameGen = iConfig.getParameter<bool>("IsBoostRestFrameGen");
  cutPara.IsGenRP = iConfig.getParameter<bool>("IsGenRP");
  cutPara.IsGenB = iConfig.getParameter<bool>("IsGenB");
  cutPara.b_genmin = iConfig.getParameter<double>("b_genmin");
  cutPara.b_genmax = iConfig.getParameter<double>("b_genmax");
  pol_lam_mean = iConfig.getParameter<double>("pol_lam_mean");
  pol_lam_sigma = iConfig.getParameter<double>("pol_lam_sigma");
  cutPara.IsGenAcc = iConfig.getParameter<bool>("IsGenAcc");
}

LamPolGenAnalyzer::~LamPolGenAnalyzer()
{}

void LamPolGenAnalyzer::beginJob()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
      hcos2p[itrg] = theOutputs->make<TH1D>(Form("cos2p_trg%d",itrg),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*})", 10000, -1, 1);
      hcos3p[itrg] = theOutputs->make<TH1D>(Form("cos3p_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
      hcos3p_p[itrg] = theOutputs->make<TH1D>(Form("cos3p_p_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
      hcos3p_m[itrg] = theOutputs->make<TH1D>(Form("cos3p_m_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
      hcos3p_rp[itrg] = theOutputs->make<TH1D>(Form("cos3p_rp_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#Psi_{RP})", 10000, -1, 1);
//      hcos1p_p1vsp2[itrg] = theOutputs->make<TH2D>(Form("cos1p_p1vsp2_trg%d",itrg),";cos(#phi_{p1}^{*});cos(#phi_{p2}^{*})", 100, -1, 1, 100, -1, 1);
//      hsin1p_p1vsp2[itrg] = theOutputs->make<TH2D>(Form("sin1p_p1vsp2_trg%d",itrg),";sin(#phi_{p1}^{*});sin(#phi_{p2}^{*})", 100, -1, 1, 100, -1, 1);
  }

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hetaphi_lam[itrg] = theOutputs->make<TH2D>(Form("etaphi_lam_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI);
    hetaphi_dau1[itrg] = theOutputs->make<TH2D>(Form("etaphi_dau1_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI); 
    hetaphi_dau2[itrg] = theOutputs->make<TH2D>(Form("etaphi_dau2_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI);
    hcos1p[itrg] = theOutputs->make<TH1D>(Form("cos1p_trg%d",itrg),";cos(#phi_{p}^{*})", 100, -1, 1);
    hsin1p[itrg] = theOutputs->make<TH1D>(Form("sin1p_trg%d",itrg),";sin(#phi_{p}^{*})", 100, -1, 1);
    hphi1p[itrg] = theOutputs->make<TH1D>(Form("phi1p_trg%d",itrg),";#phi_{p}^{*}", 100, -4, 4);
    hsin1p_rp[itrg] = theOutputs->make<TH1D>(Form("sin1p_rp_trg%d",itrg),";sin(#phi_{p}^{*}-#Psi_{RP})", 100, -8/0.642/PI, 8/0.642/PI);
    hcos1p_rp[itrg] = theOutputs->make<TH1D>(Form("cos1p_rp_trg%d",itrg),";cos(#phi_{p}^{*}-#Psi_{RP})", 100, -8/0.642/PI, 8/0.642/PI);
    hphi1p_rp[itrg] = theOutputs->make<TH1D>(Form("phi1p_rp_trg%d",itrg),";#phi_{p}^{*}-#Psi_{RP}", 100, -2*PI, 2*PI);
    htheta_star[itrg] = theOutputs->make<TH1D>(Form("theta_star_trg%d",itrg),";#theta_{p}^{*}", 100, -4, 4);
  }

  hcos2p_ref = theOutputs->make<TH1D>("cos2p_ref",";cos(2#phi_{1}-2#phi_{2})", 10000, -1, 1);
/*
  hcos1p_p_ref = theOutputs->make<TH1D>("cos1p_p_ref",";cos(2#phi)", 10000, -1, 1);
  hcos1p_m_ref = theOutputs->make<TH1D>("cos1p_m_ref",";cos(2#phi)", 10000, -1, 1);
  hsin1p_p_ref = theOutputs->make<TH1D>("sin1p_p_ref",";sin(2#phi)", 10000, -1, 1);
  hsin1p_m_ref = theOutputs->make<TH1D>("sin1p_m_ref",";sin(2#phi)", 10000, -1, 1);
*/
  hcos_ref_rp = theOutputs->make<TH1D>("cos_ref_rp",";cos(2#phi_{1}-2#Psi_{RP})", 10000, -1, 1);
  
  DiHadronCorrelationMultiBase::beginJob();
}

void LamPolGenAnalyzer::endJob()
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

void LamPolGenAnalyzer::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  psi0_gen = eventcorr.epangle;
  TVector3 rp_vector(TMath::Cos(psi0_gen), TMath::Sin(psi0_gen), 0);
  TVector3 beam_vector(0,0,1.0);
  TVector3 angmom_vector = rp_vector.Cross(beam_vector);

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
    unsigned int nasssize = eventcorr.pVect_ass[0].size();

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg1 = (eventcorr.pVect_trg[itrg])[ntrg];	  
      double effweight_trg1 = (eventcorr.effVect_trg[itrg])[ntrg];
      double eta_trg1 = pvector_trg1.Eta();
      double phi_trg1 = pvector_trg1.Phi();

      TLorentzVector pvector_trg1_dau1 = (eventcorr.pVect_trg_dau1[itrg])[ntrg];
      double eta_trg1_dau1 = pvector_trg1_dau1.Eta();
      double phi_trg1_dau1 = pvector_trg1_dau1.Phi();

      TLorentzVector pvector_trg1_dau2 = (eventcorr.pVect_trg_dau2[itrg])[ntrg];
      double eta_trg1_dau2 = pvector_trg1_dau2.Eta();
      double phi_trg1_dau2 = pvector_trg1_dau2.Phi();

      hetaphi_lam[itrg]->Fill(eta_trg1,phi_trg1);
      hetaphi_dau1[itrg]->Fill(eta_trg1_dau1,phi_trg1_dau1);
      hetaphi_dau2[itrg]->Fill(eta_trg1_dau2,phi_trg1_dau2);
      hcos1p[itrg]->Fill(TMath::Cos(phi_trg1_dau1),1.0/effweight_trg1);
      hsin1p[itrg]->Fill(TMath::Sin(phi_trg1_dau1),1.0/effweight_trg1);
      hphi1p[itrg]->Fill(phi_trg1_dau1,1.0/effweight_trg1);
      hsin1p_rp[itrg]->Fill(TMath::Sin(phi_trg1_dau1-psi0_gen)*8/0.642/PI,1.0/effweight_trg1);
      hcos1p_rp[itrg]->Fill(TMath::Cos(phi_trg1_dau1-psi0_gen)*8/0.642/PI,1.0/effweight_trg1);
      hphi1p_rp[itrg]->Fill(phi_trg1_dau1-psi0_gen,1.0/effweight_trg1);
        
      double theta_star = (pvector_trg1_dau1.Vect()).Angle(angmom_vector);
      htheta_star[itrg]->Fill(theta_star,1.0/effweight_trg1);

      for(unsigned int mtrg=ntrg+1;mtrg<ntrgsize;mtrg++)
      {
        TLorentzVector pvector_trg2 = (eventcorr.pVect_trg[itrg])[mtrg];
        double effweight_trg2 = (eventcorr.effVect_trg[itrg])[mtrg];

        TLorentzVector pvector_trg2_dau1 = (eventcorr.pVect_trg_dau1[itrg])[mtrg];
//        double eta_trg2_dau1 = pvector_trg2_dau1.Eta();
        double phi_trg2_dau1 = pvector_trg2_dau1.Phi();

        TLorentzVector pvector_trg2_dau2 = (eventcorr.pVect_trg_dau2[itrg])[mtrg];
//        double eta_trg2_dau2 = pvector_trg2_dau2.Eta();
//        double phi_trg2_dau2 = pvector_trg2_dau2.Phi();

        hcos2p[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1)),1.0/effweight_trg2/effweight_trg1);
//        hcos1p_p1vsp2[itrg]->Fill(TMath::Cos(phi_trg1_dau1),TMath::Cos(phi_trg2_dau1));
//        hsin1p_p1vsp2[itrg]->Fill(TMath::Sin(phi_trg1_dau1),TMath::Sin(phi_trg2_dau1));
//        hcos3p_rp[itrg]->Fill(TMath::Cos(phi_trg2_dau1+phi_trg1_dau1-2*psi0_gen),1.0/effweight_trg2/effweight_trg1);
        hcos3p_rp[itrg]->Fill(TMath::Cos(phi_trg2_dau1+phi_trg1_dau1-2*psi0_gen));

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];   
          double phi_ass = pvector_ass.Phi();
          double eta_ass = pvector_ass.Eta();

          hcos3p[itrg]->Fill(TMath::Cos(phi_trg2_dau1+phi_trg1_dau1-2*phi_ass),1.0/effweight_trg2/effweight_trg1);
          if(eta_ass>0) hcos3p_p[itrg]->Fill(TMath::Cos(phi_trg2_dau1+phi_trg1_dau1-2*phi_ass),1.0/effweight_trg2/effweight_trg1);
          if(eta_ass<0) hcos3p_m[itrg]->Fill(TMath::Cos(phi_trg2_dau1+phi_trg1_dau1-2*phi_ass),1.0/effweight_trg2/effweight_trg1);
        }
      }
    }
  } 

  unsigned int nasssize = eventcorr.pVect_ass[0].size();
/*
  double qsin_p = 0;
  double qcos_p = 0;
  double npair_p = 0;
  double qsin_m = 0;
  double qcos_m = 0;
  double npair_m = 0;
*/
  for(unsigned int nass=0;nass<nasssize;nass++)
  {
    TLorentzVector pvector_ass1 = (eventcorr.pVect_ass[0])[nass];
    double eta_ass1 = pvector_ass1.Eta();
    double phi_ass1 = pvector_ass1.Phi();

    hcos_ref_rp->Fill(TMath::Cos(2*psi0_gen-2*phi_ass1));

    if(eta_ass1>0) continue;

    for(unsigned int mass=0;mass<nasssize;mass++)
    {
      TLorentzVector pvector_ass2 = (eventcorr.pVect_ass[0])[mass];
      double eta_ass2 = pvector_ass2.Eta();
      double phi_ass2 = pvector_ass2.Phi();
      if(eta_ass2<0) continue;

      hcos2p_ref->Fill(TMath::Cos(2*phi_ass1-2*phi_ass2));
    }   

/*
    if(eta_ass1>0) 
    {
      qsin_p += sin(2*phi_ass1);
      qcos_p += cos(2*phi_ass1);
      npair_p++;
    }

    if(eta_ass1<0)
    {
      qsin_m += sin(2*phi_ass1);
      qcos_m += cos(2*phi_ass1);
      npair_m++;
    }   
      
    if(npair_p) hcos1p_p_ref->Fill(qcos_p/npair_p,npair_p);
    if(npair_m) hcos1p_m_ref->Fill(qcos_m/npair_m,npair_m);
    if(npair_p) hsin1p_p_ref->Fill(qsin_p/npair_p,npair_p);
    if(npair_m) hsin1p_m_ref->Fill(qsin_m/npair_m,npair_m);

    double Qvect = qcos_p*qcos_m + qsin_p*qsin_m;
    if(npair_p && npair_m) hcos2p_ref->Fill(Qvect/npair_p/npair_m,npair_p*npair_m);
*/
  }
}
