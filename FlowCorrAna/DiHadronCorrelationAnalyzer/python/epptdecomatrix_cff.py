import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epptdecomatrix_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

epptdecomatrix_ana_HI = epptdecomatrix_ana.clone(
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  etatrgmin = cms.double(-2.4),
  etatrgmax = cms.double(2.4),
  etaassmin = cms.double(-2.4),
  etaassmax = cms.double(2.4),

  EffFileName = cms.string('')
)

epptdecomatrix_ana_PbPb2018 = epptdecomatrix_ana.clone(
  xvtxcenter = cms.double(0.094),
  yvtxcenter = cms.double(-0.064),
  zvtxcenter = cms.double(0.1),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('2018PbPb_Efficiency_GeneralTracks_MB.root'),
  EffHistName = cms.string('Eff3D'),

  FakFileName = cms.string('2018PbPb_Efficiency_GeneralTracks_MB.root'),
  FakHistName = cms.string('Fak3D'),

  AssociateID = cms.string('')
)

