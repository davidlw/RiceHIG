#ifndef DiHadronCorrelationMultiAnalyzerChAsym_
#define DiHadronCorrelationMultiAnalyzerChAsym_

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

class DiHadronCorrelationMultiAnalyzerChAsym : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignal[MAXCHASYMBINS];
   TH2D* hBackground[MAXCHASYMBINS];
   TH2D* hCorrelation[MAXCHASYMBINS];
   TH2D* hSignal_pt1pt2;
   TH2D* hBackground_pt1pt2;
   TH2D* hCorrelation_pt1pt2;

   // parameters
   double signalTrgEffWeight;
   double bkgTrgEffWeight;
   double bkgAssEffWeight;
   int    bkgFactor;

   vector<double>  chasymmin;
   vector<double>  chasymmax;

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   DiHadronCorrelationMultiAnalyzerChAsym(const edm::ParameterSet&);
   ~DiHadronCorrelationMultiAnalyzerChAsym();
};
#endif  // DiHadronCorrelationMultiAnalyzerChAsym_
