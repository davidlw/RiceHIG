#ifndef ScalarProdVnAnalyzerNew_
#define ScalarProdVnAnalyzerNew_

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

class ScalarProdVnAnalyzerNew : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms
   TH2D* hPairCosn_hfp[100];
   TH2D* hPairSinn_hfp[100];
   TH2D* hPairCosn_hfm[100];
   TH2D* hPairSinn_hfm[100];
   TH2D* hCosnTrg[100];
   TH2D* hSinnTrg[100];
   TH2D* hCosnAss_hfp;
   TH2D* hSinnAss_hfp;
   TH2D* hCosnAss_hfm;
   TH2D* hSinnAss_hfm;
   TH2D* hPairCosnAss;
   TH2D* hPairSinnAss;

   // parameters
   double etaBinWidth;

//   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

//   virtual void NormalizeHists();
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:
   ScalarProdVnAnalyzerNew(const edm::ParameterSet&);
//   ~ScalarProdVnAnalyzerNew();
};
#endif  // ScalarProdVnAnalyzerNew_
