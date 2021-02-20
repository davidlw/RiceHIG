import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epptdeconew_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

epptdeco_ana_HI = epptdeco_ana.clone(
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

epptdeco_ana_PbPb2018 = epptdeco_ana.clone(
  xvtxcenter = cms.double(0.094),
  yvtxcenter = cms.double(-0.064),
  zvtxcenter = cms.double(0.1),

  EffFileName = cms.string('EffCorrectionsPixelPbPb2018_v1.root'),
  EffHistName = cms.string('Eff_50_100')
)


epptdeco_ana_pPb = epptdeco_ana.clone(
)

epptdeco_ana_120150_seq = cms.Sequence(hltHM120150*epptdeco_ana_pPb)
epptdeco_ana_150185_seq = cms.Sequence(hltHM150185*epptdeco_ana_pPb)
epptdeco_ana_185220_seq = cms.Sequence(hltHM185220*epptdeco_ana_pPb)
epptdeco_ana_220260_seq = cms.Sequence(hltHM220*epptdeco_ana_pPb)
epptdeco_ana_260_seq = cms.Sequence(hltHM220*epptdeco_ana_pPb)
