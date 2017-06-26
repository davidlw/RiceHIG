#ifndef DiHadronCorrelationMultiAnalyzerQ2_
#define DiHadronCorrelationMultiAnalyzerQ2_

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

class DiHadronCorrelationMultiAnalyzerQ2 : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignal[MAXQ2BINS];
   TH2D* hBackground[MAXQ2BINS];
   TH2D* hCorrelation[MAXQ2BINS];
   TH2D* hSignal_pt1pt2;
   TH2D* hBackground_pt1pt2;
   TH2D* hCorrelation_pt1pt2;

   // parameters
   double signalTrgEffWeight;
   double bkgTrgEffWeight;
   double bkgAssEffWeight;
   int    bkgFactor;

   vector<double>  q2min;
   vector<double>  q2max;

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   DiHadronCorrelationMultiAnalyzerQ2(const edm::ParameterSet&);
   ~DiHadronCorrelationMultiAnalyzerQ2();
};
#endif  // DiHadronCorrelationMultiAnalyzerQ2_
