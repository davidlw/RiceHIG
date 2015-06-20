// -*- C++ -*-
//
// Package:    XiNTAnalyzer
// Class:      XiNTAnalyzer
// 
/**\class XiNTAnalyzer XiNTAnalyzer.cc RiceHIG/V0Analysis/src/XiNTAnalyzer.cc

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

#include "RiceHIG/V0Analysis/interface/XiNTAnalyzer.h"

// Constructor
XiNTAnalyzer::XiNTAnalyzer(const edm::ParameterSet& iConfig) 
{
  using std::string;

  vertexCollName_ = iConfig.getParameter<edm::InputTag>("vertexCollName");
  xiCollName_     = iConfig.getParameter<edm::InputTag>("xiCollName");
/*
  etaCutMin_      = iConfig.getParameter<float>("etaCutMin");
  etaCutMax_      = iConfig.getParameter<float>("etaCutMax");
  ptCut1_         = iConfig.getParameter<float>("ptCut1");
  ptCut2_         = iConfig.getParameter<float>("ptCut2");
  nHitCut1_       = iConfig.getParameter<int>("nHitCut1");
  nHitCut2_       = iConfig.getParameter<int>("nHitCut2");
  dxySigCut1_     = iConfig.getParameter<float>("dxySigCut1");
  dxySigCut2_     = iConfig.getParameter<float>("dxySigCut2");
  dzSigCut1_      = iConfig.getParameter<float>("dzSigCut1");
  dzSigCut2_      = iConfig.getParameter<float>("dzSigCut2");
  vtxChi2Cut_     = iConfig.getParameter<float>("vtxChi2Cut");
  cosThetaCut_    = iConfig.getParameter<float>("cosThetaCut");
  decayLSigCut_   = iConfig.getParameter<float>("decayLSigCut");
*/
}

// (Empty) Destructor
XiNTAnalyzer::~XiNTAnalyzer() {

}

//
// Methods
//

// Producer Method
void XiNTAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

//   using std::vector;
   using namespace edm;
//   using namespace reco;
    
    // select on requirement of valid vertex
   edm::Handle<reco::VertexCollection> vertices;
   iEvent.getByLabel(vertexCollName_,vertices);
   float bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
   float bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
   const reco::Vertex & vtx = (*vertices)[0];
   bestvz = vtx.z(); bestvx = vtx.x(); bestvy = vtx.y();
   bestvzError = vtx.zError(); bestvxError = vtx.xError(); bestvyError = vtx.yError();
//   if(bestvz < -15.0 || bestvz>15.0) return;

   edm::Handle<reco::VertexCompositeCandidateCollection> xicandidates;
   iEvent.getByLabel(xiCollName_,xicandidates);
   if(!xicandidates.isValid()) return;

   // Create auto_ptr for each collection to be stored in the Event
   float nt_data[46];
   for( reco::VertexCompositeCandidateCollection::const_iterator xicand = xicandidates->begin();
         xicand != xicandidates->end();
         xicand++) {

       float secvz_v0=-999.9, secvx_v0=-999.9, secvy_v0=-999.9;
       float secvz_xi=-999.9, secvx_xi=-999.9, secvy_xi=-999.9;

//       const reco::VertexCompositeCandidate * v0cand = xicand->daughter(0);
       const reco::Candidate * v0cand = xicand->daughter(0);
       const reco::Candidate * d3 = xicand->daughter(1);
       const reco::Candidate * d1 = v0cand->daughter(0);
       const reco::Candidate * d2 = v0cand->daughter(1);

       reco::TrackRef dau1 = d1->get<reco::TrackRef>();
       reco::TrackRef dau2 = d2->get<reco::TrackRef>();
       reco::TrackRef dau3 = d3->get<reco::TrackRef>();

       //pt,mass
       float eta_v0 = v0cand->eta();
       float phi_v0 = v0cand->phi();
       float pt_v0 = v0cand->pt();
       float px_v0 = v0cand->px();
       float py_v0 = v0cand->py();
       float pz_v0 = v0cand->pz();
       float mass_v0 = v0cand->mass();
       float vtxChi2_v0 = v0cand->vertexChi2();
       secvz_v0 = v0cand->vz(); secvx_v0 = v0cand->vx(); secvy_v0 = v0cand->vy();

       float eta_xi = xicand->eta();
       float phi_xi = xicand->phi();
       float pt_xi = xicand->pt();
       float px_xi = xicand->px();
       float py_xi = xicand->py();
       float pz_xi = xicand->pz();
       float mass_xi = xicand->mass();
       float vtxChi2_xi = xicand->vertexChi2();
       secvz_xi = xicand->vz(); secvx_xi = xicand->vx(); secvy_xi = xicand->vy();
       float xivzError = xicand->vertexCovariance(2,2); float xivxError = xicand->vertexCovariance(0,0); float xivyError = xicand->vertexCovariance(1,1);

       //DCA
       math::XYZPoint bestvtx(bestvx,bestvy,bestvz);
       math::XYZPoint xivtx(secvx_xi,secvy_xi,secvz_xi);

       float eta_dau1 = dau1->eta();
       float phi_dau1 = dau1->phi();
       float pt_dau1 = dau1->pt();
       float pterror_dau1 = dau1->ptError();
       float chi2n_dau1 = dau1->normalizedChi2();
       float nhits_dau1 = dau1->numberOfValidHits();
       float dzbest1 = dau1->dz(xivtx);
       float dxybest1 = dau1->dxy(xivtx);
       float dzerror1 = sqrt(dau1->dzError()*dau1->dzError()+xivzError*xivzError);
       float dxyerror1 = sqrt(dau1->d0Error()*dau1->d0Error()+xivxError*xivyError);

       float eta_dau2 = dau2->eta();
       float phi_dau2 = dau2->phi();
       float pt_dau2 = dau2->pt();
       float pterror_dau2 = dau2->ptError();
       float chi2n_dau2 = dau2->normalizedChi2();
       float nhits_dau2 = dau2->numberOfValidHits();
       float dzbest2 = dau2->dz(xivtx);
       float dxybest2 = dau2->dxy(xivtx);
       float dzerror2 = sqrt(dau2->dzError()*dau2->dzError()+xivzError*xivzError);
       float dxyerror2 = sqrt(dau2->d0Error()*dau2->d0Error()+xivxError*xivyError);

       float eta_dau3 = dau3->eta();
       float phi_dau3 = dau3->phi();
       float pt_dau3 = dau3->pt();
       float pterror_dau3 = dau3->ptError();
       float chi2n_dau3 = dau3->normalizedChi2();
       float nhits_dau3 = dau3->numberOfValidHits();
       float dzbest3 = dau3->dz(bestvtx);
       float dxybest3 = dau3->dxy(bestvtx);
       float dzerror3 = sqrt(dau3->dzError()*dau3->dzError()+bestvzError*bestvzError);
       float dxyerror3 = sqrt(dau3->d0Error()*dau3->d0Error()+bestvxError*bestvyError);

       //PAngle
       TVector3 ptosvec_xi(secvx_xi-bestvx,secvy_xi-bestvy,secvz_xi-bestvz);
       TVector3 secvec_xi(px_xi,py_xi,pz_xi);
       float agl_xi = cos(secvec_xi.Angle(ptosvec_xi));

       //Decay length
       typedef ROOT::Math::SMatrix<double, 3, 3, ROOT::Math::MatRepSym<double, 3> > SMatrixSym3D;
       typedef ROOT::Math::SVector<double, 3> SVector3;
       SMatrixSym3D totalCov_xi = vtx.covariance() + xicand->vertexCovariance();
       SVector3 distanceVector_xi(secvx_xi-bestvx,secvy_xi-bestvy,secvz_xi-bestvz);
       float dl_xi = ROOT::Math::Mag(distanceVector_xi);
       float dlerror_xi = sqrt(ROOT::Math::Similarity(totalCov_xi, distanceVector_xi))/dl_xi;

       TVector3 ptosvec_v0(secvx_v0-secvx_xi,secvy_v0-secvy_xi,secvz_v0-secvz_xi);
       TVector3 secvec_v0(px_v0,py_v0,pz_v0);
       float agl_v0 = cos(secvec_v0.Angle(ptosvec_v0));

       SMatrixSym3D totalCov_v0 = v0cand->vertexCovariance() + xicand->vertexCovariance();
       SVector3 distanceVector_v0(secvx_v0-secvx_xi,secvy_v0-secvy_xi,secvz_v0-secvz_xi);
       float dl_v0 = ROOT::Math::Mag(distanceVector_v0);
       float dlerror_v0 = sqrt(ROOT::Math::Similarity(totalCov_v0, distanceVector_v0))/dl_v0;

       nt_data[0] = eta_xi;
       nt_data[1] = phi_xi;
       nt_data[2] = pt_xi;
       nt_data[3] = mass_xi;
       nt_data[4] = vtxChi2_xi;
       nt_data[5] = agl_xi;
       nt_data[6] = dl_xi;
       nt_data[7] = dlerror_xi;
       nt_data[8] = eta_v0;
       nt_data[9] = phi_v0;
       nt_data[10] = pt_v0;
       nt_data[11] = mass_v0;
       nt_data[12] = vtxChi2_v0;
       nt_data[13] = agl_v0;
       nt_data[14] = dl_v0;
       nt_data[15] = dlerror_v0;
       nt_data[16] = eta_dau1;
       nt_data[17] = phi_dau1;
       nt_data[18] = pt_dau1;
       nt_data[19] = pterror_dau1;
       nt_data[20] = chi2n_dau1;
       nt_data[21] = nhits_dau1;
       nt_data[22] = dzbest1;
       nt_data[23] = dzerror1;
       nt_data[24] = dxybest1;
       nt_data[25] = dxyerror1;
       nt_data[26] = eta_dau2;
       nt_data[27] = phi_dau2;
       nt_data[28] = pt_dau2;
       nt_data[29] = pterror_dau2;
       nt_data[30] = chi2n_dau2;
       nt_data[31] = nhits_dau2;
       nt_data[32] = dzbest2;
       nt_data[33] = dzerror2;
       nt_data[34] = dxybest2;
       nt_data[35] = dxyerror2;
       nt_data[36] = eta_dau3;
       nt_data[37] = phi_dau3;
       nt_data[38] = pt_dau3;
       nt_data[39] = pterror_dau3;
       nt_data[40] = chi2n_dau3;
       nt_data[41] = nhits_dau3;
       nt_data[42] = dzbest3;
       nt_data[43] = dzerror3;
       nt_data[44] = dxybest3;
       nt_data[45] = dxyerror3;

       xiNtuple->Fill(nt_data);
   }
}


void XiNTAnalyzer::beginJob() {
  xiNtuple = theDQMstore->make<TNtuple>("xintuple","Xi ntuple","eta_xi:phi_xi:pt_xi:mass_xi:vtxChi2_xi:agl_xi:dl_xi:dlerror_xi:eta_v0:phi_v0:pt_v0:mass_v0:vtxChi2_v0:agl_v0:dl_v0:dlerror_v0:eta_dau1:phi_dau1:pt_dau1:pterror_dau1:chi2n_dau1:nhits_dau1:dz1:dzerror1:dxy1:dxyerror1:eta_dau2:phi_dau2:pt_dau2:pterror_dau2:chi2n_dau2:nhits_dau2:dz2:dzerror2:dxy2:dxyerror2:eta_dau3:phi_dau3:pt_dau3:pterror_dau3:chi2n_dau3:nhits_dau3:dz3:dzerror3:dxy3:dxyerror3");
}


void XiNTAnalyzer::endJob() {
}
