#ifndef MultiplicityAnalyzer_
#define MultiplicityAnalyzer_

#include <exception>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <math.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
//#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"
#include "DataFormats/HcalRecHit/interface/HFRecHit.h"
#include "DataFormats/HcalRecHit/interface/HORecHit.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//#include "RecoHI/HiCentralityAlgos/interface/CentralityProvider.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/CutParameters.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationEvent.h"

class TBranch;
class TClonesArray;
class TH1D;
class TH2D;
class TH3D;
class TList;
class TTree;
class TNtuple;
class TVector3;
class TLorentzVector;
class DiHadronCorrelationEvent;

using namespace std;
using namespace reco;
using namespace edm;

#define PI 3.141592

class MultiplicityAnalyzer : public edm::EDAnalyzer {
   
 protected:
   
   edm::Service<TFileService> theOutputs;
   edm::EDGetTokenT<reco::TrackCollection> token_tracks;
   edm::EDGetTokenT<reco::VertexCollection> token_vertices;
   edm::EDGetTokenT<reco::GenParticleCollection> token_genparticles;

   // histograms
   TH2D*  hEffWeight;
   TH1D*  hTrgWeight;
   TH1D*  hNVtx;
   TH1D*  hZVtx;
   TH2D*  hXYVtx;
   TH2D*  hMultRawVsGen;
   TH2D*  hMultCorrVsGen;
   TH2D*  hMultRawVsPt_eta1;
   TH2D*  hMultRawVsPtCorr_eta1;
   TH2D*  hMultRawVsPt_eta2;
   TH2D*  hMultRawVsPtCorr_eta2;
   TH2D*  hMultRawVsPt_eta3;
   TH2D*  hMultRawVsPtCorr_eta3;
   TH1D*  hMultRaw;
   TH1D*  hMultCorr;

   // parameters
   CutParameters cutPara;
   int  nMult;
   double nMultCorr;
   int nMultGen;
   int  nVertices;
   unsigned int  maxofflinetracks;
   double  xVtx;
   double  yVtx;
   double  zVtx;
   double  xVtxError;
   double  yVtxError;
   double  zVtxError;
  
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   //virtual void endJob() ;
   virtual void beginJob();
   virtual void endJob();

   virtual void GetMult(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   virtual void GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   virtual double GetTrgWeight(double nmult);
   virtual double GetEffWeight(double eta, double pt);
   
 public:

   explicit MultiplicityAnalyzer(const edm::ParameterSet&);
   ~MultiplicityAnalyzer() {};
};
#endif  // MultiplicityAnalyzer_
