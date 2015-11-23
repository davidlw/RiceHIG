#ifndef LamPolDataAnalyzer_
#define LamPolDataAnalyzer_

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

class LamPolDataAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hcos2p[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hcos3p[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hcos1p[MAXPTTRGBINS];
   TH1D* hphi1p[MAXPTTRGBINS];
   TH1D* hcos2p_ref[MAXPTASSBINS];

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   
 public:
   LamPolDataAnalyzer(const edm::ParameterSet&);
   ~LamPolDataAnalyzer();
};
#endif  // LamPolDataAnalyzer_
