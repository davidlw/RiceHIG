#ifndef EPPtDecoAnalyzerSPMatrixNew_
#define EPPtDecoAnalyzerSPMatrixNew_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TProfile2D;
class TTree;
class TList;

class EPPtDecoAnalyzerSPMatrixNew : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms
   TProfile2D* hSignalPtCosn[5];
   TProfile2D* hSignalPtSinn[5];
   TProfile2D* hSinglePtCosn[5];
   TProfile2D* hSinglePtSinn[5];

   // parameters
   int nPtBins;
   std::vector<double> ptBins;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(DiHadronCorrelationEvent& eventcorr_trg);
   virtual double getPtBinCenter(int ibin, const std::vector<double>& ptBins); 
   
 public:
   EPPtDecoAnalyzerSPMatrixNew(const edm::ParameterSet&);

};
#endif  // EPPtDecoAnalyzerSPMatrixNew_
