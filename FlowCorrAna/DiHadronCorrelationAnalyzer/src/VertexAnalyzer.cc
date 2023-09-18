#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/VertexAnalyzer.h"
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

VertexAnalyzer::VertexAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
}

//VertexAnalyzer::~VertexAnalyzer()
//{}

//
// member functions
//

void VertexAnalyzer::beginJob()
{
  vertexTree = theOutputs->make<TTree>("vertexTree","vertexTree");
  vertexTree->Branch("RunNb",&runNb,"RunNb/i");
  vertexTree->Branch("LSNb",&lsNb,"LSNb/i");
  vertexTree->Branch("EventNb",&eventNb,"EventNb/i");
  vertexTree->Branch("nVertices",&nVertices,"nVertices/i");
  vertexTree->Branch("xVtxArr",xVtxArr,"xVtxArr[nVertices]/F");
  vertexTree->Branch("yVtxArr",yVtxArr,"yVtxArr[nVertices]/F");
  vertexTree->Branch("zVtxArr",zVtxArr,"zVtxArr[nVertices]/F");
  vertexTree->Branch("nTracks",nTracks,"nTracks[nVertices]/i");
  vertexTree->Branch("trackWeightVtx",trackWeightVtx,"trackWeightVtx[nVertices][800]/F");
  vertexTree->Branch("trackPtVtx",trackPtVtx,"trackPtVtx[nVertices][800]/F");
  vertexTree->Branch("trackPtErrVtx",trackPtErrVtx,"trackPtErrVtx[nVertices][800]/F");
  vertexTree->Branch("trackXVtx",trackXVtx,"trackXVtx[nVertices][800]/F");
  vertexTree->Branch("trackYVtx",trackYVtx,"trackYVtx[nVertices][800]/F");
  vertexTree->Branch("trackZVtx",trackZVtx,"trackZVtx[nVertices][800]/F");
  vertexTree->Branch("trackHPVtx",trackHPVtx,"trackHPVtx[nVertices][800]/O");

//  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------

void VertexAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  GetVertices(iEvent,iSetup);
}

void VertexAnalyzer::endJob()
{}

void VertexAnalyzer::GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    edm::Handle< reco::VertexCollection > vertices;
    iEvent.getByToken(token_vertices, vertices);
    if(!vertices->size()) { cout<<"Invalid or empty vertex collection!"<<endl; return; }

    edm::Handle< reco::TrackCollection > tracks;
    iEvent.getByToken(token_tracks, tracks);
    if(!tracks->size()) { cout<<"Invalid or empty track collection!"<<endl; return; }

    runNb = iEvent.id().run();
    eventNb = iEvent.id().event();
    lsNb = iEvent.luminosityBlock();

    nVertices=0;
    for(unsigned int iv=0; iv<vertices->size(); ++iv)
    {
      const reco::Vertex & vtx = (*vertices)[iv];

      if(!vtx.isFake() && vtx.tracksSize()>=2)
      {
        xVtxArr[nVertices] = vtx.x();
        yVtxArr[nVertices] = vtx.y();
        zVtxArr[nVertices] = vtx.z();
        trackSizeVtx[nVertices] = vtx.tracksSize();
        chi2Vtx[nVertices] = vtx.chi2();
        ndofVtx[nVertices] = vtx.ndof(); 

        uint nTracksTmp=0;
        for (reco::Vertex::trackRef_iterator iTrack = vtx.tracks_begin(); iTrack != vtx.tracks_end(); ++iTrack) {

           reco::TrackRef track = iTrack->castTo<reco::TrackRef>();

           trackWeightVtx[nVertices][nTracksTmp] = vtx.trackWeight(*iTrack);
           trackPtVtx[nVertices][nTracksTmp] = track->pt();
           trackPtErrVtx[nVertices][nTracksTmp] = track->ptError();
           trackXVtx[nVertices][nTracksTmp] = track->vx();
           trackYVtx[nVertices][nTracksTmp] = track->vy();
           trackZVtx[nVertices][nTracksTmp] = track->vz();
           trackHPVtx[nVertices][nTracksTmp] = track->quality(reco::TrackBase::highPurity);

//std::cout<<trackWeightVtx[nVertices][nTracksTmp]<<" "<<trackPtVtx[nVertices][nTracksTmp]<<std::endl;

           nTracksTmp++; 
        }
        nTracks[nVertices] = nTracksTmp;

        nVertices++;
      }
    }

    vertexTree->Fill();
}
