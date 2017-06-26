import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.chasymdihadroncorrelation_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

corr_ana_pPb = corr_ana.clone(
  pttrgmin = cms.vdouble(0.3),
  pttrgmax = cms.vdouble(3.0),
  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(3.0),

#  EffFileName = cms.string('')
)

corr_ana_PbPb = corr_ana_pPb.clone()
