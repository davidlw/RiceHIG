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
class TProfile2D;
class TTree;
class TList;

class EPEtaPtDecoAnalyzerSPMatrix : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TProfile2D* hSignalCosn[5];
   TProfile2D* hBackgroundCosn[5];
   TProfile2D* hSignalSinn[5];
   TProfile2D* hBackgroundSinn[5];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   virtual int getEtaBin(double eta, double etamin, double etamax, double binwidth); 
   
 public:
   EPEtaPtDecoAnalyzerSPMatrix(const edm::ParameterSet&);
   ~EPEtaPtDecoAnalyzerSPMatrix();

};
#endif  // EPEtaPtDecoAnalyzerSPMatrix_
