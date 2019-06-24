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
  trackTree->Branch("pTTRK",pT,"pTTRK[candSizeTRK]/s");
  trackTree->Branch("etaTRK",eta,"etaTRK[candSizeTRK]/S");
  trackTree->Branch("phiTRK",phi,"phiTRK[candSizeTRK]/S");
  trackTree->Branch("weightTRK",weight,"weightTRK[candSizeTRK]/s");
  
//  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------

void TrackAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  GetVertices(iEvent,iSetup);
  LoopTracks(iEvent,iSetup,1);
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
     if(fabs(trk.ptError())/trk.pt() > 0.1) continue;

     pT[candSizeTRK]  = (int)(trk.pt()*100);
     if(pT[candSizeTRK]<30) continue;

     eta[candSizeTRK] = (int)(trk.eta()*100);
     if(fabs(eta[candSizeTRK])>240) continue;

     math::XYZPoint bestvtx(xVtx,yVtx,zVtx);
     double dzvtx = trk.dz(bestvtx);
     double dxyvtx = trk.dxy(bestvtx);
     double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
     double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
     double pterror = trk.ptError();
     if(fabs(dzvtx/dzerror) > 3.0) continue;
     if(fabs(dxyvtx/dxyerror) > 3.0) continue;

     phi[candSizeTRK] = (int)(trk.phi()*100);
     weight[candSizeTRK] = (int)(GetEffWeight(eta[candSizeTRK]/100.,phi[candSizeTRK]/100.,pT[candSizeTRK]/100.,0,-1,0)*100);
    
     candSizeTRK++;
   }
   trackTree->Fill();
}

void TrackAnalyzer::endJob()
{}

void TrackAnalyzer::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{}
