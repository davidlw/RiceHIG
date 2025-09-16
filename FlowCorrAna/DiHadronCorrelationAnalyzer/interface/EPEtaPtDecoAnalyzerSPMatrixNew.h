#ifndef EPEtaPtDecoAnalyzerSPMatrixNew_
#define EPEtaPtDecoAnalyzerSPMatrixNew_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TProfile;
class TProfile2D;
class TTree;
class TList;

class EPEtaPtDecoAnalyzerSPMatrixNew : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms
   TProfile2D* hSignalCosn[5];
   TProfile2D* hSignalSinn[5];
   TProfile* hSingleCosn[5];
   TProfile* hSingleSinn[5];
   TProfile* hSingleCos2n[5];
   TProfile* hSingleSin2n[5];

   // parameters
   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(DiHadronCorrelationEvent& eventcorr);
   virtual int getEtaBin(double eta, double etamin, double etamax, double binwidth); 
   
 public:
   EPEtaPtDecoAnalyzerSPMatrixNew(const edm::ParameterSet&);

};
#endif  // EPEtaPtDecoAnalyzerSPMatrixNew_
