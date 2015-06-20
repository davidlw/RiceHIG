// -*- C++ -*-
//
// Package:    MyNtrkFilter
// Class:      MyNtrkFilter
// 
/**\class MyNtrkFilter MyNtrkFilter.cc RiceHIG/MyNtrkFilter/src/MyNtrkFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Wei Li
//         Created:  Sat Jun 20 15:48:43 EDT 2015
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

//
// class declaration
//

class MyNtrkFilter : public edm::EDFilter {
   public:
      explicit MyNtrkFilter(const edm::ParameterSet&);
      ~MyNtrkFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      edm::InputTag vertexCollName_;
      edm::InputTag trackCollName_;
      edm::InputTag genCollName_;
      double etaMin_;
      double etaMax_;
      double ptMin_;
      double ptMax_;
      int    nMultMin_;
      int    nMultMax_;
      bool   isGenMult_;
      bool   isPP_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyNtrkFilter::MyNtrkFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  vertexCollName_ = iConfig.getParameter<edm::InputTag>("vertexCollName");
  trackCollName_ = iConfig.getParameter<edm::InputTag>("trackCollName");
  genCollName_ = iConfig.getParameter<edm::InputTag>("genCollName");
  etaMin_      = iConfig.getParameter<double>("etaMin");
  etaMax_      = iConfig.getParameter<double>("etaMax");
  ptMin_         = iConfig.getParameter<double>("ptMin");
  ptMax_         = iConfig.getParameter<double>("ptMax");
  nMultMin_         = iConfig.getParameter<int>("nMultMin");
  nMultMax_         = iConfig.getParameter<int>("nMultMax");
  isGenMult_     = iConfig.getParameter<bool>("isGenMult");
  isPP_     = iConfig.getParameter<bool>("isPP");
}


MyNtrkFilter::~MyNtrkFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MyNtrkFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;

   unsigned int maxofflinetracks=0;
   double xVtx = -99999.9;
   double yVtx = -99999.9;
   double zVtx = -99999.9;
   double xVtxError = -99999.9;
   double yVtxError = -99999.9;
   double zVtxError = -99999.9;

   edm::Handle< reco::VertexCollection > vertices;
   iEvent.getByLabel(vertexCollName_, vertices);
   if(!vertices->size()) { std::cout<<"Invalid or empty vertex collection!"<<std::endl; return false; }

   for(unsigned int iv=0; iv<vertices->size(); ++iv)
   {
     const reco::Vertex & vtx = (*vertices)[iv];
     if(!vtx.isFake() && vtx.tracksSize()>=2)
     {
       if(vtx.tracksSize()>=maxofflinetracks)
       {
         xVtx = vtx.x();
         yVtx = vtx.y();
         zVtx = vtx.z();
         xVtxError = vtx.xError();
         yVtxError = vtx.yError();
         zVtxError = vtx.zError();
         maxofflinetracks = vtx.tracksSize();
       }
     }
   }

   int nMult=0;
   if(!isGenMult_)
   {
     //----- loop over tracks -----
     edm::Handle< reco::TrackCollection > tracks;
     iEvent.getByLabel(trackCollName_, tracks);
     if( !tracks->size() ) { std::cout<<"Invalid or empty track collection!"<<std::endl; return false; }

     for(unsigned it=0; it<tracks->size(); ++it){
       const reco::Track & trk = (*tracks)[it];

       if(trk.pt()<0.0001) continue;

       math::XYZPoint bestvtx(xVtx,yVtx,zVtx);

       double dzvtx = trk.dz(bestvtx);
       double dxyvtx = trk.dxy(bestvtx);
       double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
       double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);

       if(isPP_)
       {
         if(!trk.quality(reco::TrackBase::highPurity)) continue;
         if(fabs(trk.ptError())/trk.pt()>0.1) continue;
         if(fabs(dzvtx/dzerror) > 3.0) continue;
         if(fabs(dxyvtx/dxyerror) > 3.0) continue;
       }

       if(!isPP_ && !trk.quality(reco::TrackBase::highPurity)) continue;

       double eta = trk.eta();
       double pt  = trk.pt();

       if(eta>etaMin_ && eta<etaMax_ && pt>ptMin_ && pt<ptMax_) nMult++;
     }
     if(nMult<nMultMin_ || nMult>=nMultMax_) return false;
   }
   else
   {
     //----- loop over particles -----
     edm::Handle<reco::GenParticleCollection> genTracks;
     iEvent.getByLabel(genCollName_, genTracks);
     if( !genTracks->size() ) { std::cout<<"Invalid or empty genParticle collection!"<<std::endl; return false; }

     for(unsigned ip=0; ip<genTracks->size(); ++ip){
       const reco::GenParticle & p = (*genTracks)[ip];
       if(p.status() != 1) continue;
       if(p.charge() == 0) continue;

       double eta = p.eta();
       double pt  = p.pt();

       if(eta>etaMin_ && eta<etaMax_ && pt>ptMin_ && pt<ptMax_) nMult++;
     }
     if(nMult<nMultMin_ || nMult>=nMultMax_) return false;
   }
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
MyNtrkFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyNtrkFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyNtrkFilter);
