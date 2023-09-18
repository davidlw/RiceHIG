#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/dEdxAnalyzer.h"
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

dEdxAnalyzer::dEdxAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
  token_dedx = consumes< edm::ValueMap<reco::DeDxData> >(iConfig.getParameter<edm::InputTag>("dedxCollection"));
}

//dEdxAnalyzer::~dEdxAnalyzer()
//{}

//
// member functions
//

void dEdxAnalyzer::beginJob()
{
  h_dedx = theOutputs->make<TH2D>("hdedx",";p/q (GeV);dE/dx (au)",200,-10,10,200,0,20);
  
//  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------

void dEdxAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  GetVertices(iEvent,iSetup);
  LoopTracks(iEvent,iSetup,1);
}

void dEdxAnalyzer::LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int icharge)
{
   edm::Handle< reco::TrackCollection > tracks;
   iEvent.getByToken(token_tracks, tracks);
   if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

   Handle<edm::ValueMap<reco::DeDxData> > dEdxHandle;
   iEvent.getByToken(token_dedx, dEdxHandle);

   for(unsigned it=0; it<tracks->size(); ++it){

     const reco::Track & trk = (*tracks)[it];
   
     TrackRef tmpRef( tracks, it );

//     if(!trk.quality(reco::TrackBase::highPurity)) continue;
     if(!trk.quality(reco::TrackBase::loose)) continue;
     if(fabs(trk.ptError())/trk.pt() > 0.1) continue;
  
     double pt  = trk.pt();
     if(pt<0.03) continue;

     double eta = trk.eta();
     if(fabs(eta)>1.) continue;

     int nhits = trk.numberOfValidHits();
     if(nhits<=10) continue;

     double charge = trk.charge();

     math::XYZPoint bestvtx(xVtx,yVtx,zVtx);
     double dzvtx = trk.dz(bestvtx);
     double dxyvtx = trk.dxy(bestvtx);
     double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
     double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
     double pterror = trk.ptError();
     if(fabs(dzvtx/dzerror) > 1.5) continue;
     if(fabs(dxyvtx/dxyerror) > 1.5) continue;

     double pmom = trk.p();

     double dedx = 0;
     if(dEdxHandle.isValid()){
       const edm::ValueMap<reco::DeDxData> dEdxTrack = *dEdxHandle.product();
       dedx = dEdxTrack[tmpRef].dEdx();
     } 

     h_dedx->Fill(pmom/charge,dedx);
   }
}

void dEdxAnalyzer::endJob()
{}
