import FWCore.ParameterSet.Config as cms

selectV0CandidatesNew = cms.EDProducer('V0Selector',
  vertexCollName  = cms.InputTag('offlinePrimaryVertices'),
  v0CollName      = cms.string("generalV0CandidatesNew"),
  v0IDName        = cms.string("Kshort"),
  etaCutMin       = cms.double(-2.4),
  etaCutMax       = cms.double(2.4),
  ptCut1          = cms.double(0.0),
  ptCut2          = cms.double(0.0),
  nHitCut1        = cms.int32(3),
  nHitCut2        = cms.int32(3),
  dxySigCut1      = cms.double(1.0),
  dxySigCut2      = cms.double(1.0),
  dzSigCut1       = cms.double(1.0),
  dzSigCut2       = cms.double(1.0),
  vtxChi2Cut      = cms.double(10000.0),
  cosThetaCut     = cms.double(0.999),
  decayLSigCut    = cms.double(5.0),
  misIDMassCut   = cms.double(0.010),
  misIDMassCutEE = cms.double(0.015)
)
