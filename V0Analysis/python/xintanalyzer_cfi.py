import FWCore.ParameterSet.Config as cms

xiana = cms.EDAnalyzer('XiNTAnalyzer',
  vertexCollName  = cms.InputTag('offlinePrimaryVertices'),
  xiCollName      = cms.InputTag("generalCascadeCandidatesNew","LambdaC")
)
