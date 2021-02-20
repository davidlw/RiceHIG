#ifndef ConversionAnalyzer_
#define ConversionAnalyzer_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include <vector>
#include <string>

#define MAXCAN 500000

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class ConversionAnalyzer : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms

   TH1D* hMass;
   TH2D* hEtaPt;
   TH2D* hEtaPhi;

   TTree* cvsTree;

   uint candSizeCVS;
   float pT[MAXCAN];
   float eta[MAXCAN];
   float phi[MAXCAN];
   float mass[MAXCAN];
   float xvtxcvs[MAXCAN];
   float yvtxcvs[MAXCAN];
   float zvtxcvs[MAXCAN];
   float pca[MAXCAN];
   float dcottheta[MAXCAN];
   float dphi[MAXCAN];
   float dzhits[MAXCAN];
   float vtxchi2prob[MAXCAN];
   float d0q1[MAXCAN];
   float d0q2[MAXCAN];

//   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

//   virtual void NormalizeHists();
   virtual void LoopConversions(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg);
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:
   ConversionAnalyzer(const edm::ParameterSet&);
//   ~ConversionAnalyzer();
};
#endif  // ConversionAnalyzer_
