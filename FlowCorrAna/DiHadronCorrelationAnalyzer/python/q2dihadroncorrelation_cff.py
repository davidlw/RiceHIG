import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.q2dihadroncorrelation_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

corr_ana_pPb = corr_ana.clone(
  pttrgmin = cms.vdouble(0.3),
  pttrgmax = cms.vdouble(3.0),
  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(3.0),

  EventEngineerFlag = cms.int32(-1),

  q2min = cms.vdouble(-9999.0),
  q2max = cms.vdouble(9999.0),
)
