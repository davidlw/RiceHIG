#ifndef ScalarProdVnAnalyzer_
#define ScalarProdVnAnalyzer_

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

class ScalarProdVnAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackgroundCosn[MAXPTTRGBINS][MAXPTASSBINS];

   TH1D* hCosnCenter_trg[MAXPTTRGBINS][5];
   TH1D* hSinnCenter_trg[MAXPTTRGBINS][5];
   TH1D* hCosnCenter_ass[MAXPTASSBINS][5];
   TH1D* hSinnCenter_ass[MAXPTASSBINS][5];

   // parameters
   int    bkgFactor;
   bool   IsReCenterTrg;
   bool   IsReCenterAss;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void ReCenterTrg(const DiHadronCorrelationEvent& eventcorr_trg);
   virtual void ReCenterAss(const DiHadronCorrelationEvent& eventcorr_ass);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   ScalarProdVnAnalyzer(const edm::ParameterSet&);
   ~ScalarProdVnAnalyzer();
};
#endif  // ScalarProdVnAnalyzer_
