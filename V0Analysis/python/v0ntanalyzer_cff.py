import FWCore.ParameterSet.Config as cms

from RiceHIG.V0Analysis.v0ntanalyzer_cfi import *
v0ana_lambda = v0ana.clone()
v0ana_lambda.v0CollName = cms.InputTag("generalV0CandidatesLowPt","Lambda")
v0ana_ks = v0ana.clone()
v0ana_ks.v0CollName = cms.InputTag("generalV0CandidatesLowPt","Kshort")
