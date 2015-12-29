import FWCore.ParameterSet.Config as cms

from RiceHIG.V0Analysis.v0selector_cfi import *
selectV0CandidatesNewkshort = selectV0CandidatesNew.clone()
selectV0CandidatesNewlambda = selectV0CandidatesNew.clone(
  v0IDName = cms.string("Lambda"),
  misIDMassCut   = cms.double(0.020)
)

selectV0CandidatesNewlambdaBS = selectV0CandidatesNewlambda.clone(
  isUseVertex     = cms.bool(False),
  dzSigCut1       = cms.double(9999.0),
  dzSigCut2       = cms.double(9999.0)
)

selectV0CandidatesNewkshortBS = selectV0CandidatesNewkshort.clone(
  isUseVertex     = cms.bool(False)
  dzSigCut1       = cms.double(9999.0),
  dzSigCut2       = cms.double(9999.0)
)

selectV0CandidatesNewlambdatight = selectV0CandidatesNewlambda.clone(
  dxySigCut1      = cms.double(1.25),
  dxySigCut2      = cms.double(1.25),
  dzSigCut1       = cms.double(1.25),
  dzSigCut2       = cms.double(1.25),
  vtxChi2Cut      = cms.double(10000.0),
  cosThetaCut     = cms.double(0.9995),
  decayLSigCut    = cms.double(7.0),
)

selectV0CandidatesNewlambdaloose = selectV0CandidatesNewlambda.clone(
  dxySigCut1      = cms.double(1.),
  dxySigCut2      = cms.double(1.),
  dzSigCut1       = cms.double(1.),
  dzSigCut2       = cms.double(1.),
  vtxChi2Cut      = cms.double(10000.0),
  cosThetaCut     = cms.double(0.995),
  decayLSigCut    = cms.double(3.0),
)

selectV0CandidatesNewd0 = selectV0CandidatesNew.clone(
  v0IDName = cms.string("D0"),
  ptCut1          = cms.double(0.5),
  ptCut2          = cms.double(0.5),
  nHitCut1        = cms.int32(10),
  nHitCut2        = cms.int32(10),
  dxySigCut1      = cms.double(0.5),
  dxySigCut2      = cms.double(0.5),
  dzSigCut1       = cms.double(0.0),
  dzSigCut2       = cms.double(0.0),
  vtxChi2Cut      = cms.double(100000.0),
  cosThetaCut     = cms.double(0.98),
  decayLSigCut    = cms.double(4.0),
  misIDMassCut   = cms.double(0.000),
  misIDMassCutEE = cms.double(0.000)
)
