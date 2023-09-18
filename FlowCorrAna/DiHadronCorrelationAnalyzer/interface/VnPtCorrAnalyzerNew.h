#ifndef VnPtCorrAnalyzerNew_
#define VnPtCorrAnalyzerNew_

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

class VnPtCorrAnalyzerNew : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms
   TH2D* hPairCosn;
   TH2D* hPairCosnPt;
   TH2D* hPt;

   TH2D* hPairCosn_noweight;
   TH2D* hPairCosnPt_noweight;
   TH2D* hPt_noweight;

//   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

//   virtual void NormalizeHists();
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:
   VnPtCorrAnalyzerNew(const edm::ParameterSet&);
//   ~VnPtCorrAnalyzerNew();
};
#endif  // VnPtCorrAnalyzerNew_
