#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiBaseNew.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EventShape.h"
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

DiHadronCorrelationMultiBaseNew::DiHadronCorrelationMultiBaseNew(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{}

//
// member functions
//
// ------------ method called to for each event  -----------
void DiHadronCorrelationMultiBaseNew::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  nMult=0;
  nMultP=0;
  nMultM=0;
  nMultEtaP=0;
  nMultEtaM=0;
  nMultCorr=0;
  nMultAll_trg=0;
  nMultAllCorr_trg=0;
  nMultAll_ass=0;
  nMultAllCorr_ass=0;

  psi0_gen = -999.0;
  if(cutPara.IsGenRP) 
  {
    psi0_gen = GetRP(iEvent,iSetup,1);
    if(psi0_gen<-4.) cout<<"reaction plane outside the range"<<endl;
    while(1) 
    {
      pol_lam = gRandom->Gaus(pol_lam_mean,pol_lam_sigma);
      if(pol_lam<=1.0 && pol_lam>=-1.0) break;
    }
    hpol_lam->Fill(pol_lam);
  }

  if(cutPara.IsGenB) 
  {
    b_gen = GetRP(iEvent,iSetup,2);
    if(b_gen<cutPara.b_genmin || b_gen>cutPara.b_genmax) return;
  }

  // Select vertex
  if(cutPara.IsVtxSel)
  {
    GetVertices(iEvent,iSetup);

    hNVtx->Fill(nVertices);

    if(nVertices>cutPara.nvtxmax) return;

    double zVtxtmp = zVtx-cutPara.zvtxcenter;
    double yVtxtmp = yVtx-cutPara.yvtxcenter;
    double xVtxtmp = xVtx-cutPara.xvtxcenter;

    double rhotmp = sqrt(xVtxtmp*xVtxtmp+yVtxtmp*yVtxtmp);
    if( zVtxtmp<cutPara.zvtxmin || zVtxtmp>cutPara.zvtxmax || rhotmp<cutPara.rhomin || rhotmp>cutPara.rhomax ) return;

    hZVtx->Fill(zVtx);
    hXYVtx->Fill(xVtx,yVtx);
  }
  hiCentrality=-1;
  if(cutPara.centmin!=-1 && cutPara.centmax!=-1)
  {
    hiCentrality = GetCentralityBin(iEvent,iSetup);
    if(hiCentrality<cutPara.centmin || hiCentrality>=cutPara.centmax) return;
/*
    if(cutPara.IsDebug)
    {
      hHFTowerSum->Fill(hft);
      hHFvsNpixel->Fill(hft,npixel);
      hHFvsZDC->Fill(hft,zdc);
    }
*/
  }
  hCentrality->Fill(hiCentrality);

  if(cutPara.IsDSGenEvt && !IsDSGen(iEvent,iSetup)) return;

  // Select multiplicity
  GetMult(iEvent,iSetup);
  if((nMult<cutPara.nmin || nMult>=cutPara.nmax) && (cutPara.nmin!=-1 || cutPara.nmax!=-1)) return;
  hMultRawAll->Fill(nMult);
  if(cutPara.IsGenB) hMultVsB->Fill(nMult,b_gen);
  hMultCorrAll->Fill(nMultCorr,1.0/GetTrgWeight(nMult));
  hMultEtaAsym->Fill(nMult,(double)(nMultEtaP-nMultEtaM)/(nMultEtaP+nMultEtaM));
  hMultEtaPvsM->Fill(nMultEtaP,nMultEtaM);

  double asym = (double)(nMultP-nMultM)/(nMultP+nMultM);
  if( asym<cutPara.chargeasymmin || asym>cutPara.chargeasymmax ) return;
  hMultChargeAsym->Fill(asym);

  if(cutPara.IsEventEngineer) hEventEngineer->Fill(hiCentrality,GetEventEngineer(iEvent,iSetup,2));

  eventcorr = 0;
  eventcorr = new DiHadronCorrelationEvent();

  switch (trgID)
  {
     case kGenParticle:
       LoopParticles(iEvent,iSetup,1,cutPara.genpdgId_trg,cutPara.isstable_trg,cutPara.ischarge_trg);
       break;
     case kGenerator:
       LoopGenerators(iEvent,iSetup,1,cutPara.genpdgId_trg,cutPara.isstable_trg,cutPara.ischarge_trg);
       break;
     case kTrack:
       LoopTracks(iEvent,iSetup,1,-999);
       break;
     case kTrackP:
       LoopTracks(iEvent,iSetup,1,1);
       break;
     case kTrackM:
       LoopTracks(iEvent,iSetup,1,-1);
       break;
     case kCaloTower:
       LoopCaloTower(iEvent,iSetup,1);
       break;
     case kPFHadron:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::h);
       break;
     case kPFPhoton:
       cutPara.mass_trg=0.0;
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::gamma);
       break;
     case kPFElectron:
       cutPara.mass_trg=0.000511;
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::e);
       break;
     case kPFMuon:
       cutPara.mass_trg=0.1057;
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::mu);
       break;
     case kPFNeutral:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::h0);
       break;
     case kPFHadronHF:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::h_HF);
       break;
     case kPFEgammaHF:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::egamma_HF);
       break;
     case kKshort:
       cutPara.mass_trg=0.4976;
       LoopV0Candidates(iEvent,iSetup, 1, "Kshort",-1);
       break;
     case kLambda:
       cutPara.mass_trg=1.1159;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",-1);
       break;
     case kLambdaP:
       cutPara.mass_trg=1.1159;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",3122);
       break;
     case kLambdaM:
       cutPara.mass_trg=1.1159;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",-3122);
       break;
     case kD0:
       cutPara.mass_trg=1.86484;
       LoopV0Candidates(iEvent,iSetup, 1 , "D0",-1);
     default:
       break;
  }

  switch (assID)
  {
     case kGenParticle:
       LoopParticles(iEvent,iSetup,0,cutPara.genpdgId_ass,cutPara.isstable_ass,cutPara.ischarge_ass);
       break;     
     case kGenerator:
       LoopGenerators(iEvent,iSetup,0,cutPara.genpdgId_ass,cutPara.isstable_ass,cutPara.ischarge_ass);
       break;
     case kTrack:
       LoopTracks(iEvent,iSetup,0,-999);
       break;
     case kTrackP:
       LoopTracks(iEvent,iSetup,0,1);
       break;
     case kTrackM:
       LoopTracks(iEvent,iSetup,0,-1);
       break;
     case kCaloTower:
       LoopCaloTower(iEvent,iSetup,0);
       break;
     case kPFHadron:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::h);
       break;
     case kPFPhoton:
       cutPara.mass_trg=0.0;
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::gamma);
       break;
     case kPFElectron:
       cutPara.mass_trg=0.000511;
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::e);
       break;
     case kPFMuon:
       cutPara.mass_trg=0.1057;
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::mu);
       break;
     case kPFNeutral:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::h0);
       break;
     case kPFHadronHF:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::h_HF);
       break;
     case kPFEgammaHF:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::egamma_HF);
       break;
     case kKshort:
       cutPara.mass_ass=0.4976;
       LoopV0Candidates(iEvent,iSetup,0, "Kshort",-1);
       break;
     case kLambda:
       cutPara.mass_ass=1.1159;
       LoopV0Candidates(iEvent,iSetup,0, "Lambda",-1);
       break;
     case kLambdaP:
       cutPara.mass_ass=1.1159;
       LoopV0Candidates(iEvent,iSetup, 0, "Lambda",3122);
       break;
     case kLambdaM:
       cutPara.mass_ass=1.1159;
       LoopV0Candidates(iEvent,iSetup, 0, "Lambda",-3122);
       break;
     case kD0:
       cutPara.mass_ass=1.86484;
       LoopV0Candidates(iEvent,iSetup,0, "D0",-1);
       break;
     default:
       break;
  }

//  eventcorr->lumi = iEvent.luminosityBlock();
  eventcorr->event = iEvent.id().event();
//  eventcorr->nmult=nMult;
//  eventcorr->centbin=hiCentrality;
  eventcorr->zvtx=zVtx;
  eventcorr->epangle=psi0_gen;
  eventcorr->chasym = asym;

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    nMult_trg[itrg]=eventcorr->pVect_trg[itrg].size();
    nMultCorr_trg[itrg]=0;
    for(unsigned int ntrg=0;ntrg<nMult_trg[itrg];ntrg++) nMultCorr_trg[itrg] = nMultCorr_trg[itrg] + 1.0/(eventcorr->effVect_trg[itrg])[ntrg];
    hMult_trg[itrg]->Fill(nMult_trg[itrg]);
    hMultCorr_trg[itrg]->Fill(nMultCorr_trg[itrg]);
    (eventcorr->nMultCorrVect_trg).push_back(nMultCorr_trg[itrg]);
  }

  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    nMult_ass[jass]=eventcorr->pVect_ass[jass].size();
    nMultCorr_ass[jass]=0;
    for(unsigned int nass=0;nass<nMult_ass[jass];nass++) nMultCorr_ass[jass] = nMultCorr_ass[jass] + 1.0/(eventcorr->effVect_ass[jass])[nass];
    hMult_ass[jass]->Fill(nMult_ass[jass]);
    hMultCorr_ass[jass]->Fill(nMultCorr_ass[jass]);
    (eventcorr->nMultCorrVect_ass).push_back(nMultCorr_ass[jass]);
  }

  FillHistsSignal(*eventcorr); 

  delete eventcorr;
}

void DiHadronCorrelationMultiBaseNew::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{}
