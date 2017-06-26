#include "../interface/LamPolGenAnalyzerSP.h"
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

LamPolGenAnalyzerSP::LamPolGenAnalyzerSP(const edm::ParameterSet& iConfig) :
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

LamPolGenAnalyzerSP::~LamPolGenAnalyzerSP()
{}

void LamPolGenAnalyzerSP::beginJob()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hcos2p[itrg] = theOutputs->make<TH1D>(Form("cos2p_trg%d",itrg),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*})", 10000, -1, 1);
    hcos3p[itrg] = theOutputs->make<TH1D>(Form("cos3p_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_p[itrg] = theOutputs->make<TH1D>(Form("cos3p_p_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_m[itrg] = theOutputs->make<TH1D>(Form("cos3p_m_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_rp[itrg] = theOutputs->make<TH1D>(Form("cos3p_rp_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#Psi_{RP})", 10000, -1, 1);

// acceptance map
    hetaphi_lam[itrg] = theOutputs->make<TH2D>(Form("etaphi_lam_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI);
    hetaphi_dau1[itrg] = theOutputs->make<TH2D>(Form("etaphi_dau1_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI); 
    hetaphi_dau2[itrg] = theOutputs->make<TH2D>(Form("etaphi_dau2_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI);

    hetapt_lam[itrg] = theOutputs->make<TH2D>(Form("etapt_lam_trg%d",itrg),";#eta;p_{T} (GeV/c)", 30, -3, 3, 30, 0, 6);
    hetapt_dau1[itrg] = theOutputs->make<TH2D>(Form("etapt_dau1_trg%d",itrg),";#eta;p_{T} (GeV/c)", 30, -3, 3, 30, 0, 6);
    hetapt_dau2[itrg] = theOutputs->make<TH2D>(Form("etapt_dau2_trg%d",itrg),";#eta;p_{T} (GeV/c)", 30, -3, 3, 30, 0, 6);

// acceptance correction
    hcos1p[itrg] = theOutputs->make<TH1D>(Form("cos1p_trg%d",itrg),";cos(#phi_{p}^{*})", 100, -1, 1);
    hsin1p[itrg] = theOutputs->make<TH1D>(Form("sin1p_trg%d",itrg),";sin(#phi_{p}^{*})", 100, -1, 1);
    hphi1p[itrg] = theOutputs->make<TH1D>(Form("phi1p_trg%d",itrg),";#phi_{p}^{*}", 100, -4, 4);
    hcosuu[itrg] = theOutputs->make<TH1D>(Form("cosuu_trg%d",itrg),";cosuu", 100, -1, 1);
    hsinuu[itrg] = theOutputs->make<TH1D>(Form("sinuu_trg%d",itrg),";sinuu", 100, -1, 1);
    hcosu2v[itrg] = theOutputs->make<TH1D>(Form("cosu2v_trg%d",itrg),";cosu2v", 100, -1, 1);
    hsinu2v[itrg] = theOutputs->make<TH1D>(Form("sinu2v_trg%d",itrg),";sinu2v", 100, -1, 1);
    hcosu2v_p[itrg] = theOutputs->make<TH1D>(Form("cosu2v_p_trg%d",itrg),";cosu2v", 100, -1, 1);
    hsinu2v_p[itrg] = theOutputs->make<TH1D>(Form("sinu2v_p_trg%d",itrg),";sinu2v", 100, -1, 1);
    hcosu2v_m[itrg] = theOutputs->make<TH1D>(Form("cosu2v_m_trg%d",itrg),";cosu2v", 100, -1, 1);
    hsinu2v_m[itrg] = theOutputs->make<TH1D>(Form("sinu2v_m_trg%d",itrg),";sinu2v", 100, -1, 1);

// w.r.t real RP
    hsin1p_rp[itrg] = theOutputs->make<TH1D>(Form("sin1p_rp_trg%d",itrg),";sin(#phi_{p}^{*}-#Psi_{RP})", 100, -8/0.642/PI, 8/0.642/PI);
    hcos1p_rp[itrg] = theOutputs->make<TH1D>(Form("cos1p_rp_trg%d",itrg),";cos(#phi_{p}^{*}-#Psi_{RP})", 100, -8/0.642/PI, 8/0.642/PI);
    hphi1p_rp[itrg] = theOutputs->make<TH1D>(Form("phi1p_rp_trg%d",itrg),";#phi_{p}^{*}-#Psi_{RP}", 100, -2*PI, 2*PI);
    htheta_star[itrg] = theOutputs->make<TH1D>(Form("theta_star_trg%d",itrg),";#theta_{p}^{*}", 100, -4, 4);
  }

  hcos2p_ref = theOutputs->make<TH1D>("cos2p_ref",";cos(2#phi_{1}-2#phi_{2})", 10000, -1, 1);
  hcos1p_ref = theOutputs->make<TH1D>("cos1p_ref",";cos(2#phi_{1})", 10000, -1, 1);
  hsin1p_ref = theOutputs->make<TH1D>("sin1p_ref",";sin(2#phi_{1})", 10000, -1, 1);
  hcos1p_p_ref = theOutputs->make<TH1D>("cos1p_p_ref",";cos(2#phi_{1})", 10000, -1, 1);
  hsin1p_p_ref = theOutputs->make<TH1D>("sin1p_p_ref",";sin(2#phi_{1})", 10000, -1, 1);
  hcos1p_m_ref = theOutputs->make<TH1D>("cos1p_m_ref",";cos(2#phi_{1})", 10000, -1, 1);
  hsin1p_m_ref = theOutputs->make<TH1D>("sin1p_m_ref",";sin(2#phi_{1})", 10000, -1, 1);
  hcos_ref_rp = theOutputs->make<TH1D>("cos_ref_rp",";cos(2#phi_{1}-2#Psi_{RP})", 10000, -1, 1);
  hcos_ref_p_rp = theOutputs->make<TH1D>("cos_ref_p_rp",";cos(2#phi_{1}-2#Psi_{RP})", 10000, -1, 1);
  hcos_ref_m_rp = theOutputs->make<TH1D>("cos_ref_m_rp",";cos(2#phi_{1}-2#Psi_{RP})", 10000, -1, 1);
  
  DiHadronCorrelationMultiBase::beginJob();
}

void LamPolGenAnalyzerSP::endJob()
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

void LamPolGenAnalyzerSP::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  psi0_gen = eventcorr.epangle;
  TVector3 rp_vector(TMath::Cos(psi0_gen), TMath::Sin(psi0_gen), 0);
  TVector3 beam_vector(0,0,1.0);
  TVector3 angmom_vector = rp_vector.Cross(beam_vector);
  TComplex q2_rp(TMath::Cos(2*psi0_gen), TMath::Sin(2*psi0_gen));

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

  TComplex q2ass(cossum_ass,sinsum_ass);
  TComplex q2ass_p(cossum_p_ass,sinsum_p_ass);
  TComplex q2ass_m(cossum_m_ass,sinsum_m_ass);

  double cos2p_rp_ref = (q2ass*TComplex::Conjugate(q2_rp)).Re();
  double cos2p_rp_p_ref = (q2ass_p*TComplex::Conjugate(q2_rp)).Re();
  double cos2p_rp_m_ref = (q2ass_m*TComplex::Conjugate(q2_rp)).Re();
  double cos2p_pm_ref = (q2ass_p*TComplex::Conjugate(q2ass_m)).Re();

  hcos1p_ref->Fill(cossum_ass/npair_ass,npair_ass);
  hsin1p_ref->Fill(sinsum_ass/npair_ass,npair_ass);
  hcos1p_p_ref->Fill(cossum_p_ass/npair_p_ass,npair_p_ass);
  hsin1p_p_ref->Fill(sinsum_p_ass/npair_p_ass,npair_p_ass);
  hcos1p_m_ref->Fill(cossum_m_ass/npair_m_ass,npair_m_ass);
  hsin1p_m_ref->Fill(sinsum_m_ass/npair_m_ass,npair_m_ass);
  if(npair_ass) hcos_ref_rp->Fill(cos2p_rp_ref/npair_ass,npair_ass);
  if(npair_p_ass) hcos_ref_p_rp->Fill(cos2p_rp_p_ref/npair_p_ass,npair_p_ass);
  if(npair_m_ass) hcos_ref_m_rp->Fill(cos2p_rp_m_ref/npair_m_ass,npair_m_ass);
  if(npair_p_ass && npair_m_ass) hcos2p_ref->Fill(cos2p_pm_ref/npair_p_ass/npair_m_ass,npair_p_ass*npair_m_ass);

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    double sinsum_trg = 0;
    double cossum_trg = 0;
    double sin2sum_trg = 0;
    double cos2sum_trg = 0;
    double npair_trg = 0;
    double npair2_trg = 0;
    unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg1 = (eventcorr.pVect_trg[itrg])[ntrg];	  
      double effweight_trg1 = (eventcorr.effVect_trg[itrg])[ntrg];
      double eta_trg1 = pvector_trg1.Eta();
      double phi_trg1 = pvector_trg1.Phi();
      double pt_trg1 = pvector_trg1.Pt();

      TLorentzVector pvector_trg1_dau1 = (eventcorr.pVect_trg_dau1[itrg])[ntrg];
      double eta_trg1_dau1 = pvector_trg1_dau1.Eta();
      double phi_trg1_dau1 = pvector_trg1_dau1.Phi();
      double pt_trg1_dau1 = pvector_trg1_dau1.Pt();

      TLorentzVector pvector_trg1_dau2 = (eventcorr.pVect_trg_dau2[itrg])[ntrg];
      double eta_trg1_dau2 = pvector_trg1_dau2.Eta();
      double phi_trg1_dau2 = pvector_trg1_dau2.Phi();
      double pt_trg1_dau2 = pvector_trg1_dau2.Pt();

      hetaphi_lam[itrg]->Fill(eta_trg1,phi_trg1,1.0/effweight_trg1);
      hetaphi_dau1[itrg]->Fill(eta_trg1_dau1,phi_trg1_dau1,1.0/effweight_trg1);
      hetaphi_dau2[itrg]->Fill(eta_trg1_dau2,phi_trg1_dau2,1.0/effweight_trg1);

      hetapt_lam[itrg]->Fill(eta_trg1,pt_trg1,1.0/effweight_trg1);
      hetapt_dau1[itrg]->Fill(eta_trg1_dau1,pt_trg1_dau1,1.0/effweight_trg1);
      hetapt_dau2[itrg]->Fill(eta_trg1_dau2,pt_trg1_dau2,1.0/effweight_trg1);

/*
      hcos1p[itrg]->Fill(TMath::Cos(phi_trg1_dau1),1.0/effweight_trg1);
      hsin1p[itrg]->Fill(TMath::Sin(phi_trg1_dau1),1.0/effweight_trg1);
      hphi1p[itrg]->Fill(phi_trg1_dau1,1.0/effweight_trg1);
*/
      hsin1p_rp[itrg]->Fill(TMath::Sin(phi_trg1_dau1-psi0_gen)*8/0.642/PI,1.0/effweight_trg1);
      hcos1p_rp[itrg]->Fill(TMath::Cos(phi_trg1_dau1-psi0_gen)*8/0.642/PI,1.0/effweight_trg1);
      hphi1p_rp[itrg]->Fill(phi_trg1_dau1-psi0_gen,1.0/effweight_trg1);

      double theta_star = (pvector_trg1_dau1.Vect()).Angle(angmom_vector);
      htheta_star[itrg]->Fill(theta_star,1.0/effweight_trg1);

      sinsum_trg += 1.0/effweight_trg1*TMath::Sin(phi_trg1_dau1);
      cossum_trg += 1.0/effweight_trg1*TMath::Cos(phi_trg1_dau1);
      sin2sum_trg += 1.0/effweight_trg1/effweight_trg1*TMath::Sin(2*phi_trg1_dau1);
      cos2sum_trg += 1.0/effweight_trg1/effweight_trg1*TMath::Cos(2*phi_trg1_dau1);
      npair_trg += 1.0/effweight_trg1;
      npair2_trg += 1.0/effweight_trg1/effweight_trg1;
    }

    if(ntrgsize<2) continue;

    TComplex qtrg(cossum_trg,sinsum_trg);
    TComplex q2trg(cos2sum_trg,sin2sum_trg);
    double cos3p = (qtrg*qtrg*TComplex::Conjugate(q2ass)-q2trg*TComplex::Conjugate(q2ass)).Re();
    double cos3p_p = (qtrg*qtrg*TComplex::Conjugate(q2ass_p)-q2trg*TComplex::Conjugate(q2ass_p)).Re();
    double cos3p_m = (qtrg*qtrg*TComplex::Conjugate(q2ass_m)-q2trg*TComplex::Conjugate(q2ass_m)).Re();
    double cos2p = (qtrg*TComplex::Conjugate(qtrg)).Re()-npair2_trg;
    double M11 = npair_trg*npair_trg-npair2_trg;

    hcos2p[itrg]->Fill(cos2p/M11,M11);
    hcos1p[itrg]->Fill(cossum_trg/npair_trg,npair_trg);
    hsin1p[itrg]->Fill(sinsum_trg/npair_trg,npair_trg);
    if(npair_ass) hcos3p[itrg]->Fill(cos3p/M11/npair_ass,M11*npair_ass);
    if(npair_p_ass) hcos3p_p[itrg]->Fill(cos3p_p/M11/npair_p_ass,M11*npair_p_ass);
    if(npair_m_ass) hcos3p_m[itrg]->Fill(cos3p_m/M11/npair_m_ass,M11*npair_m_ass);

    double cos3p_rp = (qtrg*qtrg*TComplex::Conjugate(q2_rp)-q2trg*TComplex::Conjugate(q2_rp)).Re();
    hcos3p_rp[itrg]->Fill(cos3p_rp/M11,M11);

// acceptance correction:
    double cosuu = (qtrg*qtrg-q2trg).Re();
    double sinuu = (qtrg*qtrg-q2trg).Im();
    double cosu2v = (qtrg*TComplex::Conjugate(q2ass)).Re();
    double sinu2v = (qtrg*TComplex::Conjugate(q2ass)).Im();
    double cosu2v_p = (qtrg*TComplex::Conjugate(q2ass_p)).Re();
    double sinu2v_p = (qtrg*TComplex::Conjugate(q2ass_p)).Im();
    double cosu2v_m = (qtrg*TComplex::Conjugate(q2ass_m)).Re();
    double sinu2v_m = (qtrg*TComplex::Conjugate(q2ass_m)).Im();

    hcosuu[itrg]->Fill(cosuu/M11,M11);
    hsinuu[itrg]->Fill(sinuu/M11,M11);
    hcosu2v[itrg]->Fill(cosu2v/npair_trg/npair_ass,npair_trg*npair_ass);
    hsinu2v[itrg]->Fill(sinu2v/npair_trg/npair_ass,npair_trg*npair_ass);
    hcosu2v_p[itrg]->Fill(cosu2v_p/npair_trg/npair_p_ass,npair_trg*npair_p_ass);
    hsinu2v_p[itrg]->Fill(sinu2v_p/npair_trg/npair_p_ass,npair_trg*npair_p_ass);
    hcosu2v_m[itrg]->Fill(cosu2v_m/npair_trg/npair_m_ass,npair_trg*npair_m_ass);
    hsinu2v_m[itrg]->Fill(sinu2v_m/npair_trg/npair_m_ass,npair_trg*npair_m_ass);
  }
}
