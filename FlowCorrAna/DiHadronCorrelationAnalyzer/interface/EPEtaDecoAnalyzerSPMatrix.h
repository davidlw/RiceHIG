#ifndef EPEtaDecoAnalyzerSPMatrix_
#define EPEtaDecoAnalyzerSPMatrix_

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

#define MAXETATRGBINSMATRIX 24
#define ETATRGBINWIDTHMATRIX 0.2

class EPEtaDecoAnalyzerSPMatrix : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH2D* hBackgroundCosn[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hSignalNPairs[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hBackgroundNPairs[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPEtaDecoAnalyzerSPMatrix(const edm::ParameterSet&);
   ~EPEtaDecoAnalyzerSPMatrix();

};
#endif  // EPEtaDecoAnalyzerSPMatrix_
