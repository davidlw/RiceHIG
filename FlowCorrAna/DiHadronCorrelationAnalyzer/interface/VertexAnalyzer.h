#ifndef VertexAnalyzer_
#define VertexAnalyzer_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include <vector>
#include <string>

#define NMAXVTX 500
#define NMAXTRACKSVTX 2000

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class VertexAnalyzer : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   TTree* vertexTree;

   uint nVertices;
   uint nTracks[NMAXVTX];

   float xVtxArr[NMAXVTX];
   float yVtxArr[NMAXVTX];
   float zVtxArr[NMAXVTX];
   float trackSizeVtx[NMAXVTX];
   float chi2Vtx[NMAXVTX];
   float ndofVtx[NMAXVTX];
   float trackWeightVtx[NMAXVTX][NMAXTRACKSVTX];
   float trackPtVtx[NMAXVTX][NMAXTRACKSVTX];
   float trackXVtx[NMAXVTX][NMAXTRACKSVTX];
   float trackYVtx[NMAXVTX][NMAXTRACKSVTX];
   float trackZVtx[NMAXVTX][NMAXTRACKSVTX];

   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   
 public:
   VertexAnalyzer(const edm::ParameterSet&);
//   ~VertexAnalyzer();
};
#endif  // VertexAnalyzer_
