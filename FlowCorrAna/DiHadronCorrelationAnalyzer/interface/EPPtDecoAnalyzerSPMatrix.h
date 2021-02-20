#ifndef EPPtDecoAnalyzerSPMatrix_
#define EPPtDecoAnalyzerSPMatrix_

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

class EPPtDecoAnalyzerSPMatrix : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH1D* hSignalCosn[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackgroundCosn[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignalCosnNew[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackgroundCosnNew[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignalSinn[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackgroundSinn[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignalSinnNew[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackgroundSinnNew[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignalNpairs[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackgroundNpairs[MAXPTTRGBINS][MAXPTASSBINS];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPPtDecoAnalyzerSPMatrix(const edm::ParameterSet&);
   ~EPPtDecoAnalyzerSPMatrix();

};
#endif  // EPPtDecoAnalyzerSPMatrix_
