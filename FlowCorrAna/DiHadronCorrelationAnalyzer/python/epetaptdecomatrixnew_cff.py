import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epetaptdecomatrixnew_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

epetaptdecomatrixnew_ana_PbPb2018_mergedtracks = epetaptdecomatrixnew_ana.clone(
  xvtxcenter = cms.double(0.094),
  yvtxcenter = cms.double(-0.064),
  zvtxcenter = cms.double(0.1),

  TrgTrackCollection = cms.string(''),

  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('EffCorrectionsPixel_NTT_pt_0_10_v2.root'),
  EffHistName = cms.string('Eff_0_5')
)

epetaptdecomatrixnew_ana_PbPb2018 = epetaptdecomatrixnew_ana.clone(
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

epetaptdecomatrixnew_ana_PbPb2023 = epetaptdecomatrixnew_ana.clone(
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),

  rhomin = cms.double(0.0),
  rhomax = cms.double(1.0),
  
  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string(''),
  EffHistName = cms.string('hEff_3D'),

  FakFileName = cms.string(''),
  FakHistName = cms.string('hFak_3D'),

  AssociateID = cms.string('')
)

epetaptdecomatrixnew_ana_pp2023 = epetaptdecomatrixnew_ana.clone(
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),

  rhomin = cms.double(0.0),
  rhomax = cms.double(1.0),
  
  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(True),

  EffFileName = cms.string(''),
  EffHistName = cms.string('hEff_3D'),

  FakFileName = cms.string(''),
  FakHistName = cms.string('hFak_3D'),

  AssociateID = cms.string('')
)

epetaptdecomatrixnew_ana_OO2025 = epetaptdecomatrixnew_ana.clone(
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),

  rhomin = cms.double(0.0),
  rhomax = cms.double(1.0),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string(''),
  EffHistName = cms.string('hEff_3D'),

  FakFileName = cms.string(''),
  FakHistName = cms.string('hFak_3D'),

  AssociateID = cms.string('')
)

epetaptdecomatrixnew_ana_NeNe2025 = epetaptdecomatrixnew_ana_OO2025.clone()
