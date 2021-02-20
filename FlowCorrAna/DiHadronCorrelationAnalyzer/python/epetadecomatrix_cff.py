import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epetadecomatrix_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

epetadecomatrix_ana_PbPb2018_mergedtracks = epetadecomatrix_ana.clone(
  xvtxcenter = cms.double(0.094),
  yvtxcenter = cms.double(-0.064),
  zvtxcenter = cms.double(0.1),

  TrgTrackCollection = cms.string(''),

  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('EffCorrectionsPixel_NTT_pt_0_10_v2.root'),
  EffHistName = cms.string('Eff_0_5')
)

epetadecomatrix_ana_PbPb2018 = epetadecomatrix_ana.clone(
  xvtxcenter = cms.double(0.094),
  yvtxcenter = cms.double(-0.064),
  zvtxcenter = cms.double(0.1),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

#  EffFileName = cms.string(''),
  EffFileName = cms.string('2018PbPb_Efficiency_GeneralTracks_MB.root'),
  EffHistName = cms.string('Eff3D'),

#  FakFileName = cms.string(''),
  FakFileName = cms.string('2018PbPb_Efficiency_GeneralTracks_MB.root'),
  FakHistName = cms.string('Fak3D'),

  AssociateID = cms.string('')
)
