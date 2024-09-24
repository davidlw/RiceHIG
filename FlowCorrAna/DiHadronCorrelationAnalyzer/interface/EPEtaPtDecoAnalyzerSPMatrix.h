#ifndef EPEtaPtDecoAnalyzerSPMatrix_
#define EPEtaPtDecoAnalyzerSPMatrix_

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

class EPEtaPtDecoAnalyzerSPMatrix : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH3D* hSignalCosn[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH3D* hBackgroundCosn[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH3D* hSignalSinn[5][MAXPTTRGBINS][MAXPTASSBINS];
   TH3D* hBackgroundSinn[5][MAXPTTRGBINS][MAXPTASSBINS];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPEtaPtDecoAnalyzerSPMatrix(const edm::ParameterSet&);
   ~EPEtaPtDecoAnalyzerSPMatrix();

};
#endif  // EPEtaPtDecoAnalyzerSPMatrix_
