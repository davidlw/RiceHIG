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
   TH1D* hcos2p[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hcos3p[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hcos3p_rp[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hcos1p[MAXPTTRGBINS];
   TH1D* hsin1p_rp[MAXPTTRGBINS];
   TH1D* hcos1p_rp[MAXPTTRGBINS];
   TH1D* hphi1p[MAXPTTRGBINS];
   TH1D* htheta_star[MAXPTTRGBINS];
   TH1D* hcos2p_ref[MAXPTASSBINS];

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   
 public:
   LamPolGenAnalyzer(const edm::ParameterSet&);
   ~LamPolGenAnalyzer();
};
#endif  // LamPolGenAnalyzer_
