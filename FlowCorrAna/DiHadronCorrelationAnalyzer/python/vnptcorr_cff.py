import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.vnptcorr_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

vnptcorr_ana_pp = vnptcorr_ana.clone(

  rhomax = cms.double(0.5),

  xvtxcenter = cms.double(0.1),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(-0.4),

  zvtxmin = cms.double(-150),
  zvtxmax = cms.double(150),
  zvtxbin = cms.double(300),

#  EffFileName = cms.string('trkEff_pp_all_74X_origin.root')
  EffFileName = cms.string('pp_dijet_NTT_5TeV.root')
)

vnptcorr_ana_PbPb2018 = vnptcorr_ana.clone(

  xvtxcenter = cms.double(0.094),
  yvtxcenter = cms.double(-0.064),
  zvtxcenter = cms.double(0.1),

  EffFileName = cms.string('EffCorrectionsPixelPbPb2018_v1.root'),
  EffHistName = cms.string('Eff_50_100')
)

vnptcorr_ana_pPb = vnptcorr_ana.clone(
  rhomax = cms.double(0.5)
)
