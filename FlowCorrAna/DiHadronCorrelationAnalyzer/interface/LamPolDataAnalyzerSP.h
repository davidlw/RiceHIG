#ifndef LamPolDataAnalyzerSP_
#define LamPolDataAnalyzerSP_

#ifndef DiHadronCorrelationMultiBase_
#include "DiHadronCorrelationMultiBase.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class LamPolDataAnalyzerSP : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hlam_pol;
   TH1D* hcos2p[MAXPTTRGBINS];
   TH1D* hcos2p_pairs[MAXPTTRGBINS];
   TH2D* hcos2p_pairs_dphi[MAXPTTRGBINS];
   TH1D* hcos2p_pairs_background[MAXPTTRGBINS];
   TH2D* hcos2p_pairs_dphi_background[MAXPTTRGBINS];
   TH1D* hcos3p[MAXPTTRGBINS];
   TH1D* hcos3p_p[MAXPTTRGBINS];
   TH1D* hcos3p_m[MAXPTTRGBINS];
   TH1D* hcos3p_p_pairs[MAXPTTRGBINS];
   TH1D* hcos3p_m_pairs[MAXPTTRGBINS];
   TH2D* hcos3p_p_pairs_dphi[MAXPTTRGBINS];
   TH2D* hcos3p_m_pairs_dphi[MAXPTTRGBINS];
   TH2D* hetaphi_lam[MAXPTTRGBINS];
   TH2D* hetaphi_dau1[MAXPTTRGBINS];
   TH2D* hetaphi_dau2[MAXPTTRGBINS];
   TH2D* hdetadphi_pairs[MAXPTTRGBINS];
   TH2D* hdetadphi_lam[MAXPTTRGBINS];
   TH2D* hdetadphi_pairs_background[MAXPTTRGBINS];
   TH2D* hdetadphi_lam_background[MAXPTTRGBINS];
   TH2D* hetapt_lam[MAXPTTRGBINS];
   TH2D* hetapt_dau1[MAXPTTRGBINS];
   TH2D* hetapt_dau2[MAXPTTRGBINS];
   TH1D* hcos1p[MAXPTTRGBINS];
   TH1D* hsin1p[MAXPTTRGBINS];
   TH1D* hphi1p[MAXPTTRGBINS];
   TH1D* hcosuu[MAXPTTRGBINS];
   TH1D* hsinuu[MAXPTTRGBINS];
   TH1D* hcosu2v[MAXPTTRGBINS];
   TH1D* hsinu2v[MAXPTTRGBINS];
   TH1D* hcosu2v_p[MAXPTTRGBINS];
   TH1D* hsinu2v_p[MAXPTTRGBINS];
   TH1D* hcosu2v_m[MAXPTTRGBINS];
   TH1D* hsinu2v_m[MAXPTTRGBINS];
   TH1D* hcos2p_ref;
   TH1D* hcos1p_ref;
   TH1D* hcos1p_p_ref;
   TH1D* hcos1p_m_ref;
   TH1D* hsin1p_ref;
   TH1D* hsin1p_p_ref;
   TH1D* hsin1p_m_ref;

   double v0AglCut_;
   int    bkgFactor;

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);

 public:
   LamPolDataAnalyzerSP(const edm::ParameterSet&);
   ~LamPolDataAnalyzerSP();
};
#endif  // LamPolDataAnalyzerSP_
