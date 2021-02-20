#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/TrackAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TObjString.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TGenPhaseSpace.h>
#include <iostream>

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

TrackAnalyzer::TrackAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
}

//TrackAnalyzer::~TrackAnalyzer()
//{}

//
// member functions
//

void TrackAnalyzer::beginJob()
{
  trackTree = theOutputs->make<TTree>("trackTree","trackTree");
  trackTree->Branch("RunNb",&runNb,"RunNb/i");
  trackTree->Branch("LSNb",&lsNb,"LSNb/i");
  trackTree->Branch("EventNb",&eventNb,"EventNb/i");
  trackTree->Branch("bestvtxX",&xVtx,"bestvtxX/F");
  trackTree->Branch("bestvtxY",&yVtx,"bestvtxY/F");
  trackTree->Branch("bestvtxZ",&zVtx,"bestvtxZ/F");
  trackTree->Branch("candSizeTRK",&candSizeTRK,"candSizeTRK/i");
  trackTree->Branch("pTTRK",pT,"pTTRK[candSizeTRK]/F");
  trackTree->Branch("etaTRK",eta,"etaTRK[candSizeTRK]/F");
  trackTree->Branch("phiTRK",phi,"phiTRK[candSizeTRK]/F");
  trackTree->Branch("weightTRK",weight,"weightTRK[candSizeTRK]/F");
  if(cutPara.IsDebug)
  {
    trackTree->Branch("pTErrTRK",pTErr,"pTErrTRK[candSizeTRK]/F");   
    trackTree->Branch("dxySigTRK",dxySig,"dxySigTRK[candSizeTRK]/F");
    trackTree->Branch("dzSigTRK",dzSig,"dzSigTRK[candSizeTRK]/F");
  }
  
  genParticleTree = theOutputs->make<TTree>("genParticleTree","genParticleTree");
  genParticleTree->Branch("candSizeGEN",&candSizeGEN,"candSizeGEN/i");
  genParticleTree->Branch("pTGEN",pT,"pTGEN[candSizeGEN]/F");
  genParticleTree->Branch("etaGEN",eta,"etaGEN[candSizeGEN]/F");
  genParticleTree->Branch("phiGEN",phi,"phiGEN[candSizeGEN]/F");

//  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------

void TrackAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  GetVertices(iEvent,iSetup);
  LoopTracks(iEvent,iSetup,1);
  if(cutPara.IsGenMult) LoopParticles(iEvent,iSetup,1,-999999,1,1);
}

void TrackAnalyzer::LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int icharge)
{
   edm::Handle< reco::TrackCollection > tracks;
   iEvent.getByToken(token_tracks, tracks);

   if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

   runNb = iEvent.id().run();
   eventNb = iEvent.id().event();
   lsNb = iEvent.luminosityBlock();

   candSizeTRK = 0;
   for(unsigned it=0; it<tracks->size(); ++it){

     const reco::Track & trk = (*tracks)[it];
   
     if(!trk.quality(reco::TrackBase::highPurity)) continue;
     pTErr[candSizeTRK]=fabs(trk.ptError())/trk.pt();
//     if(!cutPara.IsDebug && (pTErr[candSizeTRK] > 0.1)) continue;
  
     pT[candSizeTRK]  = trk.pt();
//     if(!cutPara.IsDebug && pT[candSizeTRK]<0.03) continue;

     eta[candSizeTRK] = trk.eta();
//     if(!cutPara.IsDebug && fabs(eta[candSizeTRK])>2.4) continue;

     math::XYZPoint bestvtx(xVtx,yVtx,zVtx);
     double dzvtx = trk.dz(bestvtx);
     double dxyvtx = trk.dxy(bestvtx);
     double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
     double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
     double pterror = trk.ptError();
     dzSig[candSizeTRK] = fabs(dzvtx/dzerror);
     dxySig[candSizeTRK] = fabs(dxyvtx/dxyerror);
//     if(!cutPara.IsDebug && (dzSig[candSizeTRK] > 3.0)) continue;
//     if(!cutPara.IsDebug && (dxySig[candSizeTRK] > 3.0)) continue;

     phi[candSizeTRK] = trk.phi();
     weight[candSizeTRK] = GetEffWeight(eta[candSizeTRK],phi[candSizeTRK],pT[candSizeTRK],0,-1,0);

     candSizeTRK++;
   }
   trackTree->Fill();
}

void TrackAnalyzer::LoopParticles(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int pdgid, bool isstable, bool ischarge)
{
   edm::Handle<reco::GenParticleCollection> genTracks;
   iEvent.getByToken(token_genparticles, genTracks);
   if( !genTracks->size() ) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }

   candSizeGEN = 0;
   for(unsigned ip=0; ip<genTracks->size(); ++ip){
     const reco::GenParticle & p = (*genTracks)[ip];

     if(p.status() != 1 && isstable) continue;
     if(p.charge() == 0 && ischarge) continue;
     if(p.pdgId() != pdgid && pdgid!=-999999) continue;

     pTGEN[candSizeGEN]  = p.pt();
     etaGEN[candSizeGEN]  = p.eta();
     phiGEN[candSizeGEN]  = p.phi();

     candSizeGEN++;
   }
   genParticleTree->Fill();
}

void TrackAnalyzer::endJob()
{}

void TrackAnalyzer::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{}
