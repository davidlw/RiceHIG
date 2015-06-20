import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.MagneticField_cff import *
from RiceHIG.V0Analysis.v0validator_cfi import *

v0ValidatorHI = v0Validator.clone(
    trackCollection = cms.InputTag('hiSelectedTracks'),
    vertexCollection = cms.InputTag('hiSelectedVertex'),
    genParticleCollection = cms.InputTag('hiGenParticles'),
    kShortCollection = cms.InputTag('generalV0CandidatesHI:Kshort'),
    lambdaCollection = cms.InputTag('generalV0CandidatesHI:Lambda')
)
