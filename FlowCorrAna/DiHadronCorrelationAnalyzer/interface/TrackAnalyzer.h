#ifndef TrackAnalyzer_
#define TrackAnalyzer_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include <vector>
#include <string>

#define MAXCAN 50000

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class TrackAnalyzer : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   TTree* trackTree;

   uint candSizeTRK;
   uint pT[MAXCAN];
   short eta[MAXCAN];
   short phi[MAXCAN];
   uint weight[MAXCAN];

   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int icharge=999);
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:
   TrackAnalyzer(const edm::ParameterSet&);
//   ~TrackAnalyzer();
};
#endif  // TrackAnalyzer_
