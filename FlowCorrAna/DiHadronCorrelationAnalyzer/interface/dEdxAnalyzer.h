#ifndef dEdxAnalyzer_
#define dEdxAnalyzer_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include "DataFormats/TrackReco/interface/DeDxData.h"

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class dEdxAnalyzer : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   TH2D* h_dedx;

   edm::EDGetTokenT<edm::ValueMap<reco::DeDxData> > token_dedx;

   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int icharge=999);
   
 public:
   dEdxAnalyzer(const edm::ParameterSet&);
//   ~dEdxAnalyzer();
};
#endif  // dEdxAnalyzer_
