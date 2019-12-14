#ifndef RCorrelatorAnalyzer_
#define RCorrelatorAnalyzer_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class RCorrelatorAnalyzer : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms

   TH1D* hAch;

   TH2D* hEtaPhi_pos;
   TH2D* hEtaPhi_neg;

   TH1D* hNreal2_p;
   TH1D* hNreal2_m;
   TH1D* hNreal3_p;
   TH1D* hNreal3_m;
   TH1D* hNreal2perp_p;
   TH1D* hNreal2perp_m;
   TH1D* hNreal3perp_p;
   TH1D* hNreal3perp_m;

   TH1D* hNshuffle2_p;
   TH1D* hNshuffle2_m;
   TH1D* hNshuffle3_p;
   TH1D* hNshuffle3_m;
   TH1D* hNshuffle2perp_p;
   TH1D* hNshuffle2perp_m;
   TH1D* hNshuffle3perp_p;
   TH1D* hNshuffle3perp_m;

   TH1D* hAbsNreal2_p;
   TH1D* hAbsNreal2_m;
   TH1D* hAbsNreal3_p;
   TH1D* hAbsNreal3_m;
   TH1D* hAbsNreal2perp_p;
   TH1D* hAbsNreal2perp_m;
   TH1D* hAbsNreal3perp_p;
   TH1D* hAbsNreal3perp_m;

   TH1D* hAbsNshuffle2_p;
   TH1D* hAbsNshuffle2_m;
   TH1D* hAbsNshuffle3_p;
   TH1D* hAbsNshuffle3_m;
   TH1D* hAbsNshuffle2perp_p;
   TH1D* hAbsNshuffle2perp_m;
   TH1D* hAbsNshuffle3perp_p;
   TH1D* hAbsNshuffle3perp_m;

   TH1D* hR2_p;
   TH1D* hR2_m;
   TH1D* hR3_p;
   TH1D* hR3_m;

   TH1D* hAbsR2_p;
   TH1D* hAbsR2_m;
   TH1D* hAbsR3_p;
   TH1D* hAbsR3_m;

   TH2D* hCosnAss_hfp;
   TH2D* hSinnAss_hfp;
   TH2D* hCosnAss_hfm;
   TH2D* hSinnAss_hfm;
   TH2D* hPairCosnAss;
   TH2D* hPairSinnAss;

//   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

//   virtual void NormalizeHists();
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:
   RCorrelatorAnalyzer(const edm::ParameterSet&);
//   ~RCorrelatorAnalyzer();
};
#endif  // RCorrelatorAnalyzer_
