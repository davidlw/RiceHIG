// -*- C++ -*-
//
// Package:    V0NTAnalyzer
// Class:      V0NTAnalyzer
// 
/**\class V0NTAnalyzer V0NTAnalyzer.h RiceHIG/V0Analysis/interface/V0NTAnalyzer.h

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Wei Li
//
//

#ifndef RICEHIG__V0_NTANALYZER_H
#define RICEHIG__V0_NTANALYZER_H

// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include <TString.h>
#include <TVector3.h>
#include <TMatrixD.h>
#include <TNtuple.h>
  
#include <Math/Functions.h>
#include <Math/SVector.h>
#include <Math/SMatrix.h>

class V0NTAnalyzer : public edm::EDAnalyzer {
public:
  explicit V0NTAnalyzer(const edm::ParameterSet&);
  ~V0NTAnalyzer();

private:
  //virtual void beginJob() ;
  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  edm::InputTag vertexCollName_;
  edm::InputTag v0CollName_;

  TNtuple* v0Ntuple;

  edm::Service<TFileService> theDQMstore;
/*
  double ptCut1_,ptCut2_;
  int nHitCut1_,nHitCut2_;
  double etaCutMin_,etaCutMax_;
  double dxySigCut1_,dxySigCut2_,dzSigCut1_,dzSigCut2_;
  double vtxChi2Cut_;
  double cosThetaCut_;
  double decayLSigCut_;
*/
};

#endif
