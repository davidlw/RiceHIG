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
  pol_lam = iConfig.getParameter<double>("pol_lam");
}

LamPolGenAnalyzer::~LamPolGenAnalyzer()
{}

void LamPolGenAnalyzer::beginJob()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      hcos2p[itrg][jass] = theOutputs->make<TH1D>(Form("cos2p_trg%d_ass%d",itrg,jass),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*})", 10000, -1, 1);
      hcos3p[itrg][jass] = theOutputs->make<TH1D>(Form("cos3p_trg%d_ass%d",itrg,jass),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
      hcos3p_rp[itrg][jass] = theOutputs->make<TH1D>(Form("cos3p_rp_trg%d_ass%d",itrg,jass),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#Psi_{RP})", 10000, -1, 1);
    }
  }

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hcos1p[itrg] = theOutputs->make<TH1D>(Form("cos1p_trg%d",itrg),";cos(#phi_{p}^{*})", 200000, -1, 1);
    hphi1p[itrg] = theOutputs->make<TH1D>(Form("phi1p_trg%d",itrg),";#phi_{p}^{*}", 8000, -4, 4);
    hsin1p_rp[itrg] = theOutputs->make<TH1D>(Form("sin1p_rp_trg%d",itrg),";sin(#phi_{p}^{*}-#Psi_{RP})", 200000, -1, 1);
    hcos1p_rp[itrg] = theOutputs->make<TH1D>(Form("cos1p_rp_trg%d",itrg),";cos(#phi_{p}^{*}-#Psi_{RP})", 200000, -1, 1);
    htheta_star[itrg] = theOutputs->make<TH1D>(Form("theta_star_trg%d",itrg),";#theta_{p}^{*}", 8000, -4, 4);
  }

  for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
  {
    hcos2p_ref[jass] = theOutputs->make<TH1D>(Form("cos2p_ref_ass%d",jass),";cos(#phi_{1}-#phi_{2})", 10000, -1, 1);
  }
  
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
  TVector3 rp_vector(cos(psi0_gen), sin(psi0_gen), 0);
  TVector3 beam_vector(0,0,1.0);
  TVector3 angmom_vector = rp_vector.Cross(beam_vector);
//cout<<eventcorr.epangle<<endl;
//cout<<angmom_vector.X()<<" "<<angmom_vector.Y()<<" "<<angmom_vector.Z()<<endl;

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr.pVect_ass[jass].size();

      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg1 = (eventcorr.pVect_trg[itrg])[ntrg];	  
        double effweight_trg1 = (eventcorr.effVect_trg[itrg])[ntrg];
//        double eta_trg1 = pvector_trg1.Eta();
//        double phi_trg1 = pvector_trg1.Phi();
//        double pt_trg1 = pvector_trg1.Pt();
//        double eta_trg1_dau1 = -999.9;
        double phi_trg1_dau1 = -999.9;
//        double pt_trg1_dau1 = -999.9;
//        double eta_trg1_dau2 = -999.9;
//        double phi_trg1_dau2 = -999.9;
//        double pt_trg1_dau2 = -999.9;
        
        TLorentzVector pvector_trg1_dau1 = (eventcorr.pVect_trg_dau1[itrg])[ntrg];
//        eta_trg1_dau1 = pvector_trg1_dau1.Eta();
        phi_trg1_dau1 = pvector_trg1_dau1.Phi();
//        pt_trg1_dau1 = pvector_trg1_dau1.Pt();

        TLorentzVector pvector_trg1_dau2 = (eventcorr.pVect_trg_dau2[itrg])[ntrg];
//        eta_trg1_dau2 = pvector_trg1_dau2.Eta();
//        phi_trg1_dau2 = pvector_trg1_dau2.Phi();
//        pt_trg1_dau2 = pvector_trg1_dau2.Pt();
//
        hcos1p[itrg]->Fill(TMath::Cos(phi_trg1_dau1),effweight_trg1);
        hphi1p[itrg]->Fill(phi_trg1_dau1,effweight_trg1);
        hsin1p_rp[itrg]->Fill(sin(phi_trg1_dau1-psi0_gen)*8/0.642/PI,effweight_trg1);
        hcos1p_rp[itrg]->Fill(cos(phi_trg1_dau1-psi0_gen)*8/0.642/PI,effweight_trg1);
        
        double theta_star = (pvector_trg1_dau1.Vect()).Angle(angmom_vector);
        htheta_star[itrg]->Fill(theta_star,effweight_trg1);

        for(unsigned int mtrg=ntrg+1;mtrg<ntrgsize;mtrg++)
        {
          TLorentzVector pvector_trg2 = (eventcorr.pVect_trg[itrg])[mtrg];
          double effweight_trg2 = (eventcorr.effVect_trg[itrg])[mtrg];
//          double eta_trg2 = pvector_trg2.Eta();
//          double phi_trg2 = pvector_trg2.Phi();
//          double pt_trg2 = pvector_trg2.Pt();
//          double eta_trg2_dau1 = -999.9;
          double phi_trg2_dau1 = -999.9;
//          double pt_trg2_dau1 = -999.9;
//          double eta_trg2_dau2 = -999.9;
//          double phi_trg2_dau2 = -999.9;
//          double pt_trg2_dau2 = -999.9;

          TLorentzVector pvector_trg2_dau1 = (eventcorr.pVect_trg_dau1[itrg])[mtrg];
//          eta_trg2_dau1 = pvector_trg2_dau1.Eta();
          phi_trg2_dau1 = pvector_trg2_dau1.Phi();
//          pt_trg2_dau1 = pvector_trg2_dau1.Pt();

//cout<<phi_trg1_dau1<<" "<<phi_trg2_dau1<<endl;

          TLorentzVector pvector_trg2_dau2 = (eventcorr.pVect_trg_dau2[itrg])[mtrg];
//          eta_trg2_dau2 = pvector_trg2_dau2.Eta();
//          phi_trg2_dau2 = pvector_trg2_dau2.Phi();
//          pt_trg2_dau2 = pvector_trg2_dau2.Pt();

          hcos2p[itrg][jass]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1)),effweight_trg2*effweight_trg1);
          hcos3p_rp[itrg][jass]->Fill(cos(phi_trg2_dau1+phi_trg1_dau1-2*psi0_gen),effweight_trg2*effweight_trg1);
          for(unsigned int nass=0;nass<nasssize;nass++)
          {
            TLorentzVector pvector_ass = (eventcorr.pVect_ass[jass])[nass];   
            double eta_ass = pvector_ass.Eta();
            double phi_ass = pvector_ass.Phi();
//            double pt_ass = pvector_ass.Pt();

            if(fabs(eta_ass)>5 || fabs(eta_ass)<3) continue;
            hcos3p[itrg][jass]->Fill(cos(phi_trg2_dau1+phi_trg1_dau1-2*phi_ass),effweight_trg2*effweight_trg1);
          }
        }
      }
    } 

  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    unsigned int nasssize = eventcorr.pVect_ass[jass].size();
    for(unsigned int nass=0;nass<nasssize;nass++)
    {
      TLorentzVector pvector_ass1 = (eventcorr.pVect_ass[jass])[nass];
      double eta_ass1 = pvector_ass1.Eta();
      double phi_ass1 = pvector_ass1.Phi();
      if(eta_ass1>5 || eta_ass1<3) continue;

      for(unsigned int mass=0;mass<nasssize;mass++)
      {
        TLorentzVector pvector_ass2 = (eventcorr.pVect_ass[jass])[mass];
        double eta_ass2 = pvector_ass2.Eta();
        double phi_ass2 = pvector_ass2.Phi();
        if(eta_ass2>-3 || eta_ass2<-5) continue;

        hcos2p_ref[jass]->Fill(cos(2*phi_ass1-2*phi_ass2));
      }
    }
  }
}
