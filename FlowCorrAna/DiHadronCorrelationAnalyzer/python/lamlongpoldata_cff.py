import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.lamlongpoldata_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

corr_ana_cms_pPb = corr_ana.clone( etacms = cms.double(-0.46) )
corr_ana_cms_Pbp = corr_ana.clone( etacms = cms.double(0.46) )
