#ifndef DiHadronCorrelationMultiBase_
#define DiHadronCorrelationMultiBase_

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
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
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
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//#include "RecoHI/HiCentralityAlgos/interface/CentralityProvider.h"
//#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
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
using namespace HepMC;

#define PI 3.141592

class DiHadronCorrelationMultiBase : public edm::EDAnalyzer {
   
 protected:
  
   // particle types
   enum ParticleType {
     kGenParticle=0,
     kGenerator=1,
     kTrack=2,
     kTrackP=3,
     kTrackM=4,
     kJet=5,
     kMuon=6,
     kPhoton=7,
     kEcalSC=8,
     kEcalBC=9,
     kPFHadron=10,
     kPFPhoton=11,
     kPFHadronPhoton=12,
     kPFPhotonTrack=13,
     kPFElectron=14,
     kPFMuon=15,
     kPFNeutral=16,
     kPFHadronHF=17,
     kPFEgammaHF=18,
     kPionZero=19,
     kPionZeroBkgUp=20,
     kPionZeroBkgDown=21,
     kCaloTower=22,
     kEcalRecHit=23,
     kHcalRecHit=24,
     kKshort=25,
     kLambda=26,
     kLambdaP=27,
     kLambdaM=28,
     kD0=29,
     kConversion=30,
   };

   ParticleType  trgID;
   ParticleType  assID;

   //  vectors for tracks, hits etc
   DiHadronCorrelationEvent* eventcorr;
   vector<DiHadronCorrelationEvent> eventcorrArray;

//   CentralityProvider * cent;
   edm::Service<TFileService> theOutputs;

   edm::ESHandle<ParticleDataTable> pdt;

   edm::Handle<int> cbin_;
   edm::EDGetTokenT<int> tag_;
   edm::EDGetTokenT<reco::Centrality> centtag_;
   edm::EDGetTokenT<reco::TrackCollection> token_tracks;
   edm::EDGetTokenT<reco::VertexCollection> token_vertices;
   edm::EDGetTokenT<reco::GenParticleCollection> token_genparticles;
   edm::EDGetTokenT<reco::VertexCompositeCandidateCollection> token_v0candidates;
   edm::EDGetTokenT<reco::PFCandidateCollection> token_pfcandidates;
   edm::EDGetTokenT<edm::SortedCollection<CaloTower>> token_calotowers;
   edm::EDGetTokenT<reco::ConversionCollection> token_conversions;

   TNtuple* trackNtuple;

   // histograms
   TH2D*  hEffWeight;
   TH2D*  hEtaPhiWeightPos;
   TH2D*  hEtaPhiWeightNeg;
   TH1D*  hTrgWeight;
   TH1D*  hNVtx;
   TH2D*  hNVtxVsNMult;
   TH1D*  hZVtx;
   TH2D*  hXYVtx;
   TH1D*  hMultRawAll;
   TH1D*  hMultCorrAll;
   TH1D*  hMultChargeAsym;
   TH2D*  hMultEtaAsym;
   TH2D*  hMultEtaPvsM;
   TH2D*  hMultVsB;
   TH2D*  hThetaV0Plus;
   TH2D*  hThetaV0Minus;
   TH2D*  hV0InvMassVsP;
   TH2D*  hV0InvEtaVsP;
   TH2D*  hV0InvMassVsPt;
   TH2D*  hV0InvEtaVsPt;
   TH1D*  hPtAll_trg;
   TH1D*  hPTotAll_trg;
   TH2D*  hdNdetadptAll_trg;
   TH2D*  hdNdetadpAll_trg;
   TH2D*  hdNdetadphiAll_trg;
//   TH2D*  hdNdetadphiAll_dau1_trg;
//   TH2D*  hdNdetadphiAll_dau2_trg;
   TH1D*  hPtAll_ass;
   TH1D*  hPTotAll_ass;
   TH2D*  hdNdetadptAll_ass;
   TH2D*  hdNdetadpAll_ass;
   TH2D*  hdNdetadphiAll_ass;
//   TH2D*  hdNdetadphiAll_dau1_ass;
//   TH2D*  hdNdetadphiAll_dau2_ass;
   TH1D*  hPtCorrAll_trg;
   TH2D*  hdNdetadptCorrAll_trg;
   TH2D*  hdNdetadphiCorrAll_trg;
   TH1D*  hPtCorrAll_ass;
   TH2D*  hdNdetadptCorrAll_ass;
   TH2D*  hdNdetadphiCorrAll_ass;
   TH2D*  hEventEngineer;
   TH1D*  hCentrality;
   TH1D*  hHFTowerSum; 
   TH2D*  hHFvsNpixel;
   TH2D*  hHFvsZDC;
   TH1D*  hNpart;
   TH2D*  hV0InvMassVsPt_masspipicut;
   TH2D*  hV0AP;
   TH2D*  hV0AP_masspipicut;
   TH1D*  hV0MassPiPi;
   TH1D*  hV0MassEE;
   TH2D*  hInvMassVsPt_Signal;
   TH1D*  hHighPurityFrac;
   TH1D*  hpol_lam;
   TH1D*  hdzVtx;
   TH2D*  hdxyVtx;
   TH2D*  hnprivsnsec;
   TH2D*  hdxyVtx_dz1;
   TH2D*  hnprivsnsec_dz1;
   TH2D*  hLamPtvsProtonPt;
   TH2D*  hLamPtvsPionPt;
   TH2D*  hLamDauPtRatiovsLamPt; 

   TH2D*  hdNdetadphi_trg[MAXPTTRGBINS];
   TH2D*  hdNdetadphi_ass[MAXPTASSBINS];
   TH2D*  hdNdetadphiCorr_trg[MAXPTTRGBINS];
   TH2D*  hdNdetadphiCorr_ass[MAXPTASSBINS];
   TH1D*  hMult_trg[MAXPTTRGBINS];
   TH1D*  hMult_ass[MAXPTASSBINS];
   TH1D*  hMultCorr_trg[MAXPTTRGBINS];
   TH1D*  hMultCorr_ass[MAXPTASSBINS];
   TH1D*  hpT_Signal_trg[MAXPTTRGBINS];
   TH1D*  hpT_Signal_ass[MAXPTASSBINS];
   TH2D*  hpTMult_Signal_trg[MAXPTTRGBINS];
   TH2D*  hpTMult_Signal_ass[MAXPTASSBINS];
   TH1D*  hpTCorr_Signal_trg[MAXPTTRGBINS];
   TH1D*  hpTCorr_Signal_ass[MAXPTASSBINS];
   TH2D*  hpTCorrMult_Signal_trg[MAXPTTRGBINS];
   TH2D*  hpTCorrMult_Signal_ass[MAXPTASSBINS];
   TH1D*  hpT_Background_trg[MAXPTTRGBINS];
   TH1D*  hpT_Background_ass[MAXPTASSBINS];
   TH1D*  hpTCorr_Background_trg[MAXPTTRGBINS];
   TH1D*  hpTCorr_Background_ass[MAXPTASSBINS];

   // parameters
   uint runNb;
   uint eventNb;
   uint lsNb;
   CutParameters cutPara;
   int  checksign;
   int  eventClass;
   int  nEvent; 
   int  nMult;
   double  nMultP;
   double  nMultM;
   double  nMultEtaP;
   double  nMultEtaM;
   int  nMultAll_trg;
   int  nMultAll_ass;
   double nMultCorr;
   double nMultAllCorr_trg;
   double nMultAllCorr_ass;
   int  nVertices;
   unsigned int  maxofflinetracks;
   int nCentBins;
   double hft;
   double npixel;
   double zdc;
   int  NEtaBins;
   int  NPhiBins;      
   double  xVtx;
   double  yVtx;
   double  zVtx;
   double  xVtxError;
   double  yVtxError;
   double  zVtxError;
   int  hiCentrality;
   double psi0_gen;
   double b_gen;
   double pol_lam;
   double pol_lam_mean;
   double pol_lam_sigma;
   unsigned int nMult_trg[MAXPTTRGBINS];
   unsigned int nMult_ass[MAXPTASSBINS];
   double nMultCorr_trg[MAXPTTRGBINS];
   double nMultCorr_ass[MAXPTASSBINS];
   double ptMean_trg[MAXPTTRGBINS];
   double ptMean_ass[MAXPTASSBINS];
   double ptMean2_trg[MAXPTTRGBINS];
   double ptMean2_ass[MAXPTASSBINS];
  
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginRun(const edm::Run&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void GetMult(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   virtual void LoopGenerators(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int pdgid, bool isstable, bool ischarge);
   virtual void LoopParticles(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int pdgid, bool isstable, bool ischarge);    
   virtual void LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int icharge=999);
   virtual void LoopCaloTower(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg);
   virtual void LoopConversions(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg);
   virtual void LoopV0Candidates(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, TString candtype, int pdgID);
   virtual void LoopPFCandidates(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, reco::PFCandidate::ParticleType pfID);
   virtual void GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   virtual void NormalizeHists() {};
   virtual void AssignTrgPtBins(double pt, double eta, double phi, double mass, double charge, double effweight, bool isv0 = false,
                                double pt_dau1 = -999., double eta_dau1 = -999., double phi_dau1 = -999., double mass_dau1 = -999.,
                                double pt_dau2 = -999., double eta_dau2 = -999., double phi_dau2 = -999., double mass_dau2 = -999. );
   virtual void AssignAssPtBins(double pt, double eta, double phi, double mass, double charge, double effweight, bool isv0 = false,
                                double pt_dau1 = -999., double eta_dau1 = -999., double phi_dau1 = -999., double mass_dau1 = -999.,
                                double pt_dau2 = -999., double eta_dau2 = -999., double phi_dau2 = -999., double mass_dau2 = -999. );
   virtual double GetEventEngineer(const edm::Event& iEvent, const edm::EventSetup& iSetup, int nn);
   virtual double GetRP(const edm::Event& iEvent, const edm::EventSetup& iSetup, int index=1);
   virtual int  GetCentralityBin(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   virtual double GetDeltaEta(double eta_trg, double eta_ass);
   virtual double GetDeltaPhi(double phi_trg, double phi_ass);
   virtual bool   GetPttrgBin(double pt, double eta, int itrg);
   virtual bool   GetPtassBin(double pt, double eta, int jass);
   virtual double GetTrgWeight(double nmult);
   virtual double GetEffWeight(double eta, double phi, double pt, double zvtx, int centbin, double charge);
   virtual bool Acceptance(double eta, double phi, double pt);
   virtual bool IsDSGen(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   virtual ParticleType GetParticleID(TString particleid);
   
 public:

   explicit DiHadronCorrelationMultiBase(const edm::ParameterSet&);
   ~DiHadronCorrelationMultiBase() {};
};
#endif  // DiHadronCorrelationMultiBase_
