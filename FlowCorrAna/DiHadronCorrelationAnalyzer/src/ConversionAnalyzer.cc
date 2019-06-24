#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ConversionAnalyzer.h"
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

ConversionAnalyzer::ConversionAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
}

//ConversionAnalyzer::~ConversionAnalyzer()
//{}

//
// member functions
//

void ConversionAnalyzer::beginJob()
{
  hMass = theOutputs->make<TH1D>("mass",";mass",500,0,1);
  hEtaPt = theOutputs->make<TH2D>("etapt",";#eta;p_{T}",100,-5,5,100,0,10);
  hEtaPhi = theOutputs->make<TH2D>("etaphi",";#eta;#phi",100,-5,5,100,-PI,PI);

  cvsTree = theOutputs->make<TTree>("conversionTree","conversionTree");
  cvsTree->Branch("RunNb",&runNb,"RunNb/i");
  cvsTree->Branch("LSNb",&lsNb,"LSNb/i");
  cvsTree->Branch("EventNb",&eventNb,"EventNb/i");
  cvsTree->Branch("nPV",&nVertices,"nPV/S");
  cvsTree->Branch("bestvtxX",&xVtx,"bestvtxX/F");
  cvsTree->Branch("bestvtxY",&yVtx,"bestvtxY/F");
  cvsTree->Branch("bestvtxZ",&zVtx,"bestvtxZ/F");
  cvsTree->Branch("candSizeCVS",&candSizeCVS,"candSizeCVS/i");
  cvsTree->Branch("pTCVS",pT,"pTCVS[candSizeCVS]/F");
  cvsTree->Branch("etaCVS",eta,"etaCVS[candSizeCVS]/F");
  cvsTree->Branch("phiCVS",phi,"phiCVS[candSizeCVS]/F");
  cvsTree->Branch("massCVS",mass,"massCVS[candSizeCVS]/F");
  
  cvsTree->Branch("xvtxCVS",xvtxcvs,"xvtxCVS[candSizeCVS]/F");
  cvsTree->Branch("yvtxCVS",yvtxcvs,"yvtxCVS[candSizeCVS]/F");
  cvsTree->Branch("zvtxCVS",zvtxcvs,"zvtxCVS[candSizeCVS]/F");
  cvsTree->Branch("vtxchi2probCVS",vtxchi2prob,"vtxchi2prob[candSizeCVS]/F");
  cvsTree->Branch("pcaCVS",pca,"pcaCVS[candSizeCVS]/F");
  cvsTree->Branch("dcotthetaCVS",dcottheta,"dcotthetaCVS[candSizeCVS]/F");
  cvsTree->Branch("dphiCVS",dphi,"dphiCVS[candSizeCVS]/F");
  cvsTree->Branch("dzhitsCVS",dzhits,"dzhitsCVS[candSizeCVS]/F");
  cvsTree->Branch("d0q1CVS",d0q1,"d0q1CVS[candSizeCVS]/F");
  cvsTree->Branch("d0q2CVS",d0q2,"d0q2CVS[candSizeCVS]/F");

  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------
/*
void ConversionAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  DiHadronCorrelationMultiBaseNew::analyze(iEvent,iSetup);

  FillHistsSignal(*eventcorr);
}
*/

void ConversionAnalyzer::LoopConversions(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg)
{
   edm::Handle<ConversionCollection> conversions;
   iEvent.getByToken(token_conversions, conversions);
//   if(!conversions->size()) { return; }

   runNb = iEvent.id().run();
   eventNb = iEvent.id().event();
   lsNb = iEvent.luminosityBlock();
   
   candSizeCVS = 0;
   for(unsigned it=0; it<conversions->size(); ++it){

     const Conversion & conversion = (*conversions)[it];

     if(conversion.nTracks()!=2) continue;

     pT[candSizeCVS] = conversion.pairMomentum().Rho();
     eta[candSizeCVS] = conversion.pairMomentum().Eta();
     phi[candSizeCVS] = conversion.pairMomentum().Phi();
     mass[candSizeCVS] = conversion.pairInvariantMass();

     xvtxcvs[candSizeCVS] = conversion.conversionVertex().x();
     yvtxcvs[candSizeCVS] = conversion.conversionVertex().y();
     zvtxcvs[candSizeCVS] = conversion.conversionVertex().z();

     pca[candSizeCVS] = conversion.distOfMinimumApproach();
     dcottheta[candSizeCVS] = conversion.pairCotThetaSeparation();
     dphi[candSizeCVS] =  conversion.dPhiTracksAtVtx();
     dzhits[candSizeCVS] = fabs((conversion.tracksInnerPosition())[0].z()-(conversion.tracksInnerPosition())[1].z());
     vtxchi2prob[candSizeCVS] = TMath::Prob(conversion.conversionVertex().chi2(),conversion.conversionVertex().ndof());
     d0q1[candSizeCVS] = (conversion.tracksSigned_d0())[0];
     d0q2[candSizeCVS] = (conversion.tracksSigned_d0())[1];

     candSizeCVS++;

     double charge = 0.0;
     double effweight = 1.0;

     if(istrg) AssignTrgPtBins(pT[candSizeCVS],eta[candSizeCVS],phi[candSizeCVS],mass[candSizeCVS],charge,effweight);
     else AssignAssPtBins(pT[candSizeCVS],eta[candSizeCVS],phi[candSizeCVS],mass[candSizeCVS],charge,effweight);
   }
   cvsTree->Fill();
}

void ConversionAnalyzer::endJob()
{}

void ConversionAnalyzer::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{
   unsigned int ntrgsize = eventcorr.pVect_trg[0].size();

   for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
   {
     TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];
     double pt_trg = pvector_trg.Pt();
     double eta_trg = pvector_trg.Eta();
     double phi_trg = pvector_trg.Phi();
     double mass_trg = pvector_trg.M();

     hMass->Fill(mass_trg);
     hEtaPt->Fill(eta_trg,pt_trg);
     hEtaPhi->Fill(eta_trg,phi_trg);
   }
}
