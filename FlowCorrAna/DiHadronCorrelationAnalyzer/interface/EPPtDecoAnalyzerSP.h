#ifndef EPPtDecoAnalyzerSP_
#define EPPtDecoAnalyzerSP_

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

class EPPtDecoAnalyzerSP : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackgroundCosn[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hSignalCosnNew[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackgroundCosnNew[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignalNpairs[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackgroundNpairs[MAXPTTRGBINS][MAXPTASSBINS];

   float cos1[MAXPTTRGBINS][MAXETATRGBINSPT];
   float cos2[MAXPTTRGBINS][MAXETATRGBINSPT];
   float cos3[MAXPTTRGBINS][MAXETATRGBINSPT];
   float cos4[MAXPTTRGBINS][MAXETATRGBINSPT];
   float sin1[MAXPTTRGBINS][MAXETATRGBINSPT];
   float sin2[MAXPTTRGBINS][MAXETATRGBINSPT];
   float sin3[MAXPTTRGBINS][MAXETATRGBINSPT];
   float sin4[MAXPTTRGBINS][MAXETATRGBINSPT];
   float nparticles[MAXPTTRGBINS][MAXETATRGBINSPT];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPPtDecoAnalyzerSP(const edm::ParameterSet&);
   ~EPPtDecoAnalyzerSP();

};
#endif  // EPPtDecoAnalyzerSP_
