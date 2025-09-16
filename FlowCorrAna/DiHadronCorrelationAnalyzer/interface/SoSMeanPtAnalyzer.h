#ifndef SoSMeanPtAnalyzer_
#define SoSMeanPtAnalyzer_

#include <exception>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <math.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
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
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
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

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/METReco/interface/HcalCaloFlagLabels.h"
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibCalorimetry/HcalAlgos/interface/HcalPulseShapes.h"
#include "DataFormats/HcalDigi/interface/HcalQIESample.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/QWZDC2018Helper.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

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

class SoSMeanPtAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources> {
   
 protected:
   
   edm::Service<TFileService> theOutputs;
   edm::EDGetTokenT<reco::TrackCollection> token_tracks;
   edm::EDGetTokenT<reco::VertexCollection> token_vertices;
   edm::EDGetTokenT<reco::GenParticleCollection> token_genparticles;
   edm::EDGetTokenT<pat::PackedCandidateCollection> token_packedPFCandidates;
   edm::EDGetTokenT<pat::PackedGenParticleCollection> token_packedgenparticles;
   edm::EDGetTokenT<reco::Centrality> token_centrality;
   edm::EDGetTokenT<int> token_centralitybin;
   edm::InputTag zdcDigiSrc_;

   // histograms
   TH3D*  hEffWeight;
   TH3D*  hFakWeight;
   TH1D*  hTrgWeight;
   TH1D*  hNVtx;
   TH1D*  hZVtx;
   TH2D*  hXYVtx;
   TH1D*  hCentrality;

   TH1D* hHF;
   TH2D* hHFvsNpixel;
   TH2D* hHFvsZDC;
   TH2D* hHFvsZDCP;
   TH2D* hHFvsZDCM;   
   TH2D* hNVtxVsHF;
   TH2D* hCentVsHF;
   TH2D* hCentVsNpixel;
   TH2D* hCentVsZDC;

   TH2D* hCentVsPt[10];
   TH2D* hEhftowerCentRapVsPt[10];  
   TH2D* hEhfCentRapVsPt[10][6];
   TH2D* hECentVsPtMidRap[10];
   TH2D* hNCentVsPtMidRap[10];
   TH1D* hEhfcentestimator[10];
   TH1D* hEcentestimator[10];
   TH1D* hNcentestimator[10];
   
   // parameters
   CutParameters cutPara;
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

   virtual void GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   virtual double GetTrgWeight(double nmult);
   virtual double GetEffWeight(double eta, double pt, int centbin);
   
 public:

   explicit SoSMeanPtAnalyzer(const edm::ParameterSet&);
   ~SoSMeanPtAnalyzer() {};
};
#endif  // SoSMeanPtAnalyzer_
