import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.track_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

trackgen_ana = track_ana.clone()
trackgen_ana.IsGenMult = cms.bool(True)
