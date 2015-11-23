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
   TH2D* hSignalCosnSame_pm[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackgroundCosnSame_pm[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hSignalCosnSame_mp[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackgroundCosnSame_mp[MAXPTTRGBINS][MAXPTASSBINS];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   ScalarProdVnAnalyzer(const edm::ParameterSet&);
   ~ScalarProdVnAnalyzer();
};
#endif  // ScalarProdVnAnalyzer_
