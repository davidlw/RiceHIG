import FWCore.ParameterSet.Config as cms

ntrkfilter = cms.EDProducer('MyNtrkFilter',
  vertexCollName  = cms.InputTag('offlinePrimaryVertices'),
  trackCollName  = cms.InputTag('generalTracks'),
  genCollName  = cms.InputTag('genParticles'),

  etaMin       = cms.double(-2.4),
  etaMax       = cms.double(2.4),
  ptMin        = cms.double(0.0),
  ptMax        = cms.double(100000.0),
  nMultMin     = cms.int32(0),
  nMultMax     = cms.int32(100000),

  isGenMult_   = cms.bool(False),
  isPP_        = cms.bool(True)
)
