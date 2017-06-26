#include "../interface/LamPolDataAnalyzerSP.h"
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

LamPolDataAnalyzerSP::LamPolDataAnalyzerSP(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  v0AglCut_ = iConfig.getParameter<double>("v0AglCut"); 
  bkgFactor = 10;
}

LamPolDataAnalyzerSP::~LamPolDataAnalyzerSP()
{}

void LamPolDataAnalyzerSP::beginJob()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hcos2p[itrg] = theOutputs->make<TH1D>(Form("cos2p_trg%d",itrg),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*})", 10000, -1, 1);
    hcos2p_pairs[itrg] = theOutputs->make<TH1D>(Form("cos2p_pairs_trg%d",itrg),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*})", 10000, -1, 1);
    hcos2p_pairs_dphi[itrg] = theOutputs->make<TH2D>(Form("cos2p_pairs_dphi_trg%d",itrg),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*});#Delta#phi", 10000, -1, 1, 6, 0., PI);
    hcos2p_pairs_background[itrg] = theOutputs->make<TH1D>(Form("cos2p_pairs_background_trg%d",itrg),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*})", 10000, -1, 1);
    hcos2p_pairs_dphi_background[itrg] = theOutputs->make<TH2D>(Form("cos2p_pairs_dphi_background_trg%d",itrg),";cos(#phi_{p,1}^{*}-#phi_{p,2}^{*});#Delta#phi", 10000, -1, 1, 6, 0., PI);
    hcos3p[itrg] = theOutputs->make<TH1D>(Form("cos3p_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_p[itrg] = theOutputs->make<TH1D>(Form("cos3p_p_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_m[itrg] = theOutputs->make<TH1D>(Form("cos3p_m_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_p_pairs[itrg] = theOutputs->make<TH1D>(Form("cos3p_p_pairs_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_m_pairs[itrg] = theOutputs->make<TH1D>(Form("cos3p_m_pairs_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref})", 10000, -1, 1);
    hcos3p_p_pairs_dphi[itrg] = theOutputs->make<TH2D>(Form("cos3p_p_pairs_dphi_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref});#Delta#phi", 10000, -1, 1, 6, 0., PI);
    hcos3p_m_pairs_dphi[itrg] = theOutputs->make<TH2D>(Form("cos3p_m_pairs_dphi_trg%d",itrg),";cos(#phi_{p,1}^{*}+#phi_{p,2}^{*}-2#phi_{ref});#Delta#phi", 10000, -1, 1, 6, 0., PI);

// acceptance map
    hetaphi_lam[itrg] = theOutputs->make<TH2D>(Form("etaphi_lam_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI);
    hetaphi_dau1[itrg] = theOutputs->make<TH2D>(Form("etaphi_dau1_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI); 
    hetaphi_dau2[itrg] = theOutputs->make<TH2D>(Form("etaphi_dau2_trg%d",itrg),";#eta;#phi", 30, -3, 3, 32, -PI, PI);

    hetapt_lam[itrg] = theOutputs->make<TH2D>(Form("etapt_lam_trg%d",itrg),";#eta;p_{T} (GeV/c)", 30, -3, 3, 30, 0, 6);
    hetapt_dau1[itrg] = theOutputs->make<TH2D>(Form("etapt_dau1_trg%d",itrg),";#eta;p_{T} (GeV/c)", 30, -3, 3, 30, 0, 6);
    hetapt_dau2[itrg] = theOutputs->make<TH2D>(Form("etapt_dau2_trg%d",itrg),";#eta;p_{T} (GeV/c)", 30, -3, 3, 30, 0, 6);

    hdetadphi_pairs[itrg] = theOutputs->make<TH2D>(Form("detadphi_pairs_trg%d",itrg),";Delta#eta;#Delta#phi", 60*4, -6, 6, 32*4, -PI, PI);
    hdetadphi_lam[itrg] = theOutputs->make<TH2D>(Form("detadphi_lam_trg%d",itrg),";Delta#eta;#Delta#phi", 60*4, -6, 6, 32*4, -PI, PI);
    hdetadphi_pairs_background[itrg] = theOutputs->make<TH2D>(Form("detadphi_pairs_background_trg%d",itrg),";Delta#eta;#Delta#phi", 60*4, -6, 6, 32*4, -PI, PI);
    hdetadphi_lam_background[itrg] = theOutputs->make<TH2D>(Form("detadphi_lam_background_trg%d",itrg),";Delta#eta;#Delta#phi", 60*4, -6, 6, 32*4, -PI, PI);

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
  }

  hcos2p_ref = theOutputs->make<TH1D>("cos2p_ref",";cos(2#phi_{1}-2#phi_{2})", 10000, -1, 1);
  hcos1p_ref = theOutputs->make<TH1D>("cos1p_ref",";cos(2#phi_{1})", 10000, -1, 1);
  hsin1p_ref = theOutputs->make<TH1D>("sin1p_ref",";sin(2#phi_{1})", 10000, -1, 1);
  hcos1p_p_ref = theOutputs->make<TH1D>("cos1p_p_ref",";cos(2#phi_{1})", 10000, -1, 1);
  hsin1p_p_ref = theOutputs->make<TH1D>("sin1p_p_ref",";sin(2#phi_{1})", 10000, -1, 1);
  hcos1p_m_ref = theOutputs->make<TH1D>("cos1p_m_ref",";cos(2#phi_{1})", 10000, -1, 1);
  hsin1p_m_ref = theOutputs->make<TH1D>("sin1p_m_ref",";sin(2#phi_{1})", 10000, -1, 1);
  
  DiHadronCorrelationMultiBase::beginJob();
}

void LamPolDataAnalyzerSP::endJob()
{
  DiHadronCorrelationMultiBase::endJob();

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;
  cout<< "Total of " << eventcorrArray.size() << " events are selected!" << endl;

  cout<< "Start running lambda polarization analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);

    unsigned int mixstart = i+1;
    unsigned int mixend = i+1+bkgFactor;

    if(mixend>eventcorrArray.size()) mixend=eventcorrArray.size();
    for(unsigned int j=mixstart;j<mixend;j++)
    {
      double deltazvtx = eventcorrArray[i].zvtx-eventcorrArray[j].zvtx;
      if(fabs(deltazvtx)>0.3) continue;

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running lambda polarization analysis!" << endl;
}

void LamPolDataAnalyzerSP::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
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

  TComplex q2ass(cossum_ass,sinsum_ass);
  TComplex q2ass_p(cossum_p_ass,sinsum_p_ass);
  TComplex q2ass_m(cossum_m_ass,sinsum_m_ass);

  double cos2p_pm_ref = (q2ass_p*TComplex::Conjugate(q2ass_m)).Re();

  hcos1p_ref->Fill(cossum_ass/npair_ass,npair_ass);
  hsin1p_ref->Fill(sinsum_ass/npair_ass,npair_ass);
  hcos1p_p_ref->Fill(cossum_p_ass/npair_p_ass,npair_p_ass);
  hsin1p_p_ref->Fill(sinsum_p_ass/npair_p_ass,npair_p_ass);
  hcos1p_m_ref->Fill(cossum_m_ass/npair_m_ass,npair_m_ass);
  hsin1p_m_ref->Fill(sinsum_m_ass/npair_m_ass,npair_m_ass);

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
//    if(ntrgsize<2) continue;

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

      sinsum_trg += 1.0/effweight_trg1*TMath::Sin(phi_trg1_dau1);
      cossum_trg += 1.0/effweight_trg1*TMath::Cos(phi_trg1_dau1);
      sin2sum_trg += 1.0/effweight_trg1/effweight_trg1*TMath::Sin(2*phi_trg1_dau1);
      cos2sum_trg += 1.0/effweight_trg1/effweight_trg1*TMath::Cos(2*phi_trg1_dau1);
      npair_trg += 1.0/effweight_trg1;
      npair2_trg += 1.0/effweight_trg1/effweight_trg1;

      for(unsigned int mtrg=ntrg+1;mtrg<ntrgsize;mtrg++)
      {
        TLorentzVector pvector_trg2 = (eventcorr.pVect_trg[itrg])[mtrg];
        double effweight_trg2 = (eventcorr.effVect_trg[itrg])[mtrg];
        double eta_trg2 = pvector_trg2.Eta();
        TLorentzVector pvector_trg2_dau1 = (eventcorr.pVect_trg_dau1[itrg])[mtrg];
        double eta_trg2_dau1 = pvector_trg2_dau1.Eta();
//        double phi_trg2_dau1 = pvector_trg2_dau1.Phi();
        TLorentzVector pvector_trg2_dau2 = (eventcorr.pVect_trg_dau2[itrg])[mtrg];
//        double eta_trg2_dau2 = pvector_trg2_dau2.Eta();
//        double phi_trg2_dau2 = pvector_trg2_dau2.Phi();
/*
        if(fabs(eta_trg1_dau1-eta_trg2_dau1)<0.01 && fabs(phi_trg1_dau1-phi_trg2_dau1)<0.01) continue;
        if(fabs(eta_trg1_dau1-eta_trg2_dau2)<0.01 && fabs(phi_trg1_dau1-phi_trg2_dau2)<0.01) continue;
        if(fabs(eta_trg1_dau2-eta_trg2_dau1)<0.01 && fabs(phi_trg1_dau2-phi_trg2_dau1)<0.01) continue;
        if(fabs(eta_trg1_dau2-eta_trg2_dau2)<0.01 && fabs(phi_trg1_dau2-phi_trg2_dau2)<0.01) continue;
*/
        if(fabs(eta_trg1-eta_trg2)<v0AglCut_ && fabs(pvector_trg1.DeltaPhi(pvector_trg2))<v0AglCut_) continue;

        hdetadphi_pairs[itrg]->Fill(eta_trg1_dau1-eta_trg2_dau1,pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1));
        hdetadphi_lam[itrg]->Fill(eta_trg1-eta_trg2,pvector_trg1.DeltaPhi(pvector_trg2),1.0/effweight_trg1/effweight_trg2);

        TLorentzVector pvector_trg2_dau1_invert(pvector_trg2_dau1.X(),-pvector_trg2_dau1.Y(),pvector_trg2_dau1.Z(),pvector_trg2_dau1.T());

        hcos2p_pairs[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1)),1.0/effweight_trg1/effweight_trg2);
        hcos3p_p_pairs[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*cossum_p_ass/npair_p_ass+TMath::Sin(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*sinsum_p_ass/npair_p_ass,1.0/effweight_trg1/effweight_trg2*npair_p_ass);
        hcos3p_m_pairs[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*cossum_m_ass/npair_m_ass+TMath::Sin(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*sinsum_m_ass/npair_m_ass,1.0/effweight_trg1/effweight_trg2*npair_m_ass);

        hcos2p_pairs_dphi[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1)),pvector_trg1.DeltaPhi(pvector_trg2),1.0/effweight_trg1/effweight_trg2);
        hcos3p_p_pairs_dphi[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*cossum_p_ass/npair_p_ass+TMath::Sin(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*sinsum_p_ass/npair_p_ass,pvector_trg1.DeltaPhi(pvector_trg2)*sinsum_p_ass/npair_p_ass,1.0/effweight_trg1/effweight_trg2*npair_p_ass);
        hcos3p_m_pairs_dphi[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*cossum_m_ass/npair_m_ass+TMath::Sin(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1_invert))*sinsum_m_ass/npair_m_ass,pvector_trg1.DeltaPhi(pvector_trg2)*sinsum_m_ass/npair_m_ass,1.0/effweight_trg1/effweight_trg2*npair_m_ass);
      }
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

void LamPolDataAnalyzerSP::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
/*
    double sinsum_trg = 0;
    double cossum_trg = 0;
    double sin2sum_trg = 0;
    double cos2sum_trg = 0;
    double npair_trg = 0;
    double npair2_trg = 0;
*/
    unsigned int ntrgsize = eventcorr_trg.pVect_trg[itrg].size();
    unsigned int nasssize = eventcorr_ass.pVect_trg[itrg].size();
//    if(ntrgsize<2 || nasssize<2) continue;

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg1 = (eventcorr_trg.pVect_trg[itrg])[ntrg];
      double effweight_trg1 = (eventcorr_trg.effVect_trg[itrg])[ntrg];
      double eta_trg1 = pvector_trg1.Eta();
//      double phi_trg1 = pvector_trg1.Phi();
//      double pt_trg1 = pvector_trg1.Pt();

      TLorentzVector pvector_trg1_dau1 = (eventcorr_trg.pVect_trg_dau1[itrg])[ntrg];
      double eta_trg1_dau1 = pvector_trg1_dau1.Eta();
//      double phi_trg1_dau1 = pvector_trg1_dau1.Phi();
//      double pt_trg1_dau1 = pvector_trg1_dau1.Pt();

      TLorentzVector pvector_trg1_dau2 = (eventcorr_trg.pVect_trg_dau2[itrg])[ntrg];
//      double eta_trg1_dau2 = pvector_trg1_dau2.Eta();
//      double phi_trg1_dau2 = pvector_trg1_dau2.Phi();
//      double pt_trg1_dau2 = pvector_trg1_dau2.Pt();
/*
      sinsum_trg += 1.0/effweight_trg1*TMath::Sin(phi_trg1_dau1);
      cossum_trg += 1.0/effweight_trg1*TMath::Cos(phi_trg1_dau1);
      sin2sum_trg += 1.0/effweight_trg1/effweight_trg1*TMath::Sin(2*phi_trg1_dau1);
      cos2sum_trg += 1.0/effweight_trg1/effweight_trg1*TMath::Cos(2*phi_trg1_dau1);
      npair_trg += 1.0/effweight_trg1;
      npair2_trg += 1.0/effweight_trg1/effweight_trg1;
*/
      for(unsigned int mtrg=0;mtrg<nasssize;mtrg++)
      {
        TLorentzVector pvector_trg2 = (eventcorr_ass.pVect_trg[itrg])[mtrg];
        double effweight_trg2 = (eventcorr_ass.effVect_trg[itrg])[mtrg];
        double eta_trg2 = pvector_trg2.Eta();
        TLorentzVector pvector_trg2_dau1 = (eventcorr_ass.pVect_trg_dau1[itrg])[mtrg];
        double eta_trg2_dau1 = pvector_trg2_dau1.Eta();
        TLorentzVector pvector_trg2_dau2 = (eventcorr_ass.pVect_trg_dau2[itrg])[mtrg];

        if(fabs(eta_trg1-eta_trg2)<v0AglCut_ && fabs(pvector_trg1.DeltaPhi(pvector_trg2))<v0AglCut_) continue;

        hdetadphi_pairs_background[itrg]->Fill(eta_trg1_dau1-eta_trg2_dau1,pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1));
        hdetadphi_lam_background[itrg]->Fill(eta_trg1-eta_trg2,pvector_trg1.DeltaPhi(pvector_trg2),1.0/effweight_trg1/effweight_trg2);

        TLorentzVector pvector_trg2_dau1_invert(pvector_trg2_dau1.X(),-pvector_trg2_dau1.Y(),pvector_trg2_dau1.Z(),pvector_trg2_dau1.T());

        hcos2p_pairs_background[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1)),1.0/effweight_trg1/effweight_trg2);
        hcos2p_pairs_dphi_background[itrg]->Fill(TMath::Cos(pvector_trg1_dau1.DeltaPhi(pvector_trg2_dau1)),pvector_trg1.DeltaPhi(pvector_trg2),1.0/effweight_trg1/effweight_trg2);
      }
    }
  }
}
