// -*- C++ -*-
//
// Package:    V0NTAnalyzer
// Class:      V0NTAnalyzer
// 
/**\class V0NTAnalyzer V0NTAnalyzer.cc RiceHIG/V0Analysis/src/V0NTAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author: Wei Li 
//
//


// system include files
#include <memory>

#include "RiceHIG/V0Analysis/interface/V0NTAnalyzer.h"

const double piMass = 0.13957018;
const double piMassSquared = piMass*piMass;
const double protonMass = 0.93827203;
const double protonMassSquared = protonMass*protonMass;
const double electronMass = 0.000511;
const double electronMassSquared = electronMass*electronMass;
const double lambdaMass = 1.115683;
const double kshortMass = 0.497614; 

// Constructor
V0NTAnalyzer::V0NTAnalyzer(const edm::ParameterSet& iConfig) 
{
  using std::string;

  vertexCollName_ = iConfig.getParameter<edm::InputTag>("vertexCollName");
  v0CollName_     = iConfig.getParameter<edm::InputTag>("v0CollName");
/*
  etaCutMin_      = iConfig.getParameter<double>("etaCutMin");
  etaCutMax_      = iConfig.getParameter<double>("etaCutMax");
  ptCut1_         = iConfig.getParameter<double>("ptCut1");
  ptCut2_         = iConfig.getParameter<double>("ptCut2");
  nHitCut1_       = iConfig.getParameter<int>("nHitCut1");
  nHitCut2_       = iConfig.getParameter<int>("nHitCut2");
  dxySigCut1_     = iConfig.getParameter<double>("dxySigCut1");
  dxySigCut2_     = iConfig.getParameter<double>("dxySigCut2");
  dzSigCut1_      = iConfig.getParameter<double>("dzSigCut1");
  dzSigCut2_      = iConfig.getParameter<double>("dzSigCut2");
  vtxChi2Cut_     = iConfig.getParameter<double>("vtxChi2Cut");
  cosThetaCut_    = iConfig.getParameter<double>("cosThetaCut");
  decayLSigCut_   = iConfig.getParameter<double>("decayLSigCut");
*/
}

// (Empty) Destructor
V0NTAnalyzer::~V0NTAnalyzer() {

}

//
// Methods
//

// Producer Method
void V0NTAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

//   using std::vector;
   using namespace edm;
//   using namespace reco;
    
    // select on requirement of valid vertex
   edm::Handle<reco::VertexCollection> vertices;
   iEvent.getByLabel(vertexCollName_,vertices);
   double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
   double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
   const reco::Vertex & vtx = (*vertices)[0];
   bestvz = vtx.z(); bestvx = vtx.x(); bestvy = vtx.y();
   bestvzError = vtx.zError(); bestvxError = vtx.xError(); bestvyError = vtx.yError();
//   if(bestvz < -15.0 || bestvz>15.0) return;

   edm::Handle<reco::VertexCompositeCandidateCollection> v0candidates;
   iEvent.getByLabel(v0CollName_,v0candidates);
   if(!v0candidates.isValid()) return;

   // Create auto_ptr for each collection to be stored in the Event
   float nt_data[28];
   for( reco::VertexCompositeCandidateCollection::const_iterator v0cand = v0candidates->begin();
         v0cand != v0candidates->end();
         v0cand++) {

       double secvz=-999.9, secvx=-999.9, secvy=-999.9;

       const reco::Candidate * d1 = v0cand->daughter(0);
       const reco::Candidate * d2 = v0cand->daughter(1);

       reco::TrackRef dau1 = d1->get<reco::TrackRef>();
       reco::TrackRef dau2 = d2->get<reco::TrackRef>();

       //pt,mass
       double eta = v0cand->eta();
       double phi = v0cand->phi();
       double pt = v0cand->pt();
       double px = v0cand->px();
       double py = v0cand->py();
       double pz = v0cand->pz();
       double mass = v0cand->mass();
       double vtxChi2 = v0cand->vertexChi2();
       secvz = v0cand->vz(); secvx = v0cand->vx(); secvy = v0cand->vy();

       //DCA
       math::XYZPoint bestvtx(bestvx,bestvy,bestvz);

       double eta_dau1 = dau1->eta();
       double phi_dau1 = dau1->phi();
       double pt_dau1 = dau1->pt();
       double pterror_dau1 = dau1->ptError();
       double chi2n_dau1 = dau1->normalizedChi2();
       double nhits_dau1 = dau1->numberOfValidHits();
       double dzbest1 = dau1->dz(bestvtx);
       double dxybest1 = dau1->dxy(bestvtx);
       double dzerror1 = sqrt(dau1->dzError()*dau1->dzError()+bestvzError*bestvzError);
       double dxyerror1 = sqrt(dau1->d0Error()*dau1->d0Error()+bestvxError*bestvyError);
//       double dzos1 = dzbest1/dzerror1;
//       double dxyos1 = dxybest1/dxyerror1;

       double eta_dau2 = dau2->eta();
       double phi_dau2 = dau2->phi();
       double pt_dau2 = dau2->pt();
       double pterror_dau2 = dau2->ptError();
       double chi2n_dau2 = dau2->normalizedChi2();
       double nhits_dau2 = dau2->numberOfValidHits();
       double dzbest2 = dau2->dz(bestvtx);
       double dxybest2 = dau2->dxy(bestvtx);
       double dzerror2 = sqrt(dau2->dzError()*dau2->dzError()+bestvzError*bestvzError);
       double dxyerror2 = sqrt(dau2->d0Error()*dau2->d0Error()+bestvxError*bestvyError);
//       double dzos2 = dzbest2/dzerror2;
//       double dxyos2 = dxybest2/dxyerror2;

       //PAngle
       TVector3 ptosvec(secvx-bestvx,secvy-bestvy,secvz-bestvz);
       TVector3 secvec(px,py,pz);
       double agl = cos(secvec.Angle(ptosvec));

       //Decay length
       typedef ROOT::Math::SMatrix<double, 3, 3, ROOT::Math::MatRepSym<double, 3> > SMatrixSym3D;
       typedef ROOT::Math::SVector<double, 3> SVector3;
       SMatrixSym3D totalCov = vtx.covariance() + v0cand->vertexCovariance();
       SVector3 distanceVector(secvx-bestvx,secvy-bestvy,secvz-bestvz);
       double dl = ROOT::Math::Mag(distanceVector);
       double dlerror = sqrt(ROOT::Math::Similarity(totalCov, distanceVector))/dl;
//       double dlos = dl/dlerror;

       nt_data[0] = eta;
       nt_data[1] = phi;
       nt_data[2] = pt;
       nt_data[3] = mass;
       nt_data[4] = vtxChi2;
       nt_data[5] = agl;
       nt_data[6] = dl;
       nt_data[7] = dlerror;
       nt_data[8] = eta_dau1;
       nt_data[9] = phi_dau1;
       nt_data[10] = pt_dau1;
       nt_data[11] = pterror_dau1;
       nt_data[12] = chi2n_dau1;
       nt_data[13] = nhits_dau1;
       nt_data[14] = dzbest1;
       nt_data[15] = dzerror1;
       nt_data[16] = dxybest1;
       nt_data[17] = dxyerror1;
       nt_data[18] = eta_dau2;
       nt_data[19] = phi_dau2;
       nt_data[20] = pt_dau2;
       nt_data[21] = pterror_dau2;
       nt_data[22] = chi2n_dau2;
       nt_data[23] = nhits_dau2;
       nt_data[24] = dzbest2;
       nt_data[25] = dzerror2;
       nt_data[26] = dxybest2;
       nt_data[27] = dxyerror2;

       v0Ntuple->Fill(nt_data);
   }
}


void V0NTAnalyzer::beginJob() {
  v0Ntuple = theDQMstore->make<TNtuple>("v0ntuple","v0 ntuple","eta:phi:pt:mass:vtxChi2:agl:dl:dlerror:eta_dau1:phi_dau1:pt_dau1:pterror_dau1:chi2n_dau1:nhits_dau1:dz1:dzerror1:dxy1:dxyerror1:eta_dau2:phi_dau2:pt_dau2:pterror_dau2:chi2n_dau2:nhits_dau2:dz2:dzerror2:dxy2:dxyerror2");
}


void V0NTAnalyzer::endJob() {
}
