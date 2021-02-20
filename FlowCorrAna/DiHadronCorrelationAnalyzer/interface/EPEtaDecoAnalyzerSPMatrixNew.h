#ifndef EPEtaDecoAnalyzerSPMatrixNew_
#define EPEtaDecoAnalyzerSPMatrixNew_

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

#define MAXETATRGBINSMATRIX 50

class EPEtaDecoAnalyzerSPMatrixNew : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXETATRGBINSMATRIX];
   TH2D* hSignalSinn[MAXETATRGBINSMATRIX];
   TH1D* hSignalNPairs[MAXETATRGBINSMATRIX];
   TH2D* hSignalCosn2[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hSignalNPairs2[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];

   // parameters
   double    etaBinWidth;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   
 public:
   EPEtaDecoAnalyzerSPMatrixNew(const edm::ParameterSet&);
   ~EPEtaDecoAnalyzerSPMatrixNew();

};
#endif  // EPEtaDecoAnalyzerSPMatrixNew_
