import FWCore.ParameterSet.Config as cms

v0ana = cms.EDAnalyzer('V0NTAnalyzer',
  vertexCollName  = cms.InputTag('offlinePrimaryVertices'),
  v0CollName      = cms.InputTag("generalV0CandidatesNew","D0","D0RECO")
)
