#ifndef LamPolGenAnalyzer_
#define LamPolGenAnalyzer_

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

class LamPolGenAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hlam_pol;
   TH1D* hcos2p[MAXPTTRGBINS];
   TH1D* hcos3p[MAXPTTRGBINS];
   TH1D* hcos3p_p[MAXPTTRGBINS];
   TH1D* hcos3p_m[MAXPTTRGBINS];
   TH1D* hcos3p_rp[MAXPTTRGBINS];
//   TH2D* hcos1p_p1vsp2[MAXPTTRGBINS];
//   TH2D* hsin1p_p1vsp2[MAXPTTRGBINS];
   TH2D* hetaphi_lam[MAXPTTRGBINS];
   TH2D* hetaphi_dau1[MAXPTTRGBINS];
   TH2D* hetaphi_dau2[MAXPTTRGBINS];
   TH1D* hcos1p[MAXPTTRGBINS];
   TH1D* hsin1p[MAXPTTRGBINS];
   TH1D* hphi1p[MAXPTTRGBINS];
   TH1D* hsin1p_rp[MAXPTTRGBINS];
   TH1D* hcos1p_rp[MAXPTTRGBINS];
   TH1D* hphi1p_rp[MAXPTTRGBINS];
   TH1D* htheta_star[MAXPTTRGBINS];
   TH1D* hcos2p_ref;
   TH1D* hcos1p_p_ref;
   TH1D* hcos1p_m_ref;
   TH1D* hsin1p_p_ref;
   TH1D* hsin1p_m_ref;
   TH1D* hcos_ref_rp;

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);

 public:
   LamPolGenAnalyzer(const edm::ParameterSet&);
   ~LamPolGenAnalyzer();
};
#endif  // LamPolGenAnalyzer_
