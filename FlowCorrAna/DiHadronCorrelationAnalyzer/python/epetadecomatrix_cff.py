import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epetadecomatrix_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

epetadecomatrix_ana_HI_gen = epetadecomatrix_ana.clone(
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('genParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  TriggerID = cms.string('GenParticle'),
  AssociateID = cms.string('GenParticle'),

  IsGenMult = cms.bool(True),
  IsVtxSel = cms.bool(False),

  EffFileName = cms.string('')
)

epetadecomatrix_ana_HI = epetadecomatrix_ana.clone(
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('genParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('')
)

#epetadeco_ana_seq = cms.Sequence(epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
#epetadeco_ana_120150_seq = cms.Sequence(hltHM120150*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
#epetadeco_ana_150185_seq = cms.Sequence(hltHM150185*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
#epetadeco_ana_185220_seq = cms.Sequence(hltHM185220*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
#epetadeco_ana_220260_seq = cms.Sequence(hltHM220*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
#epetadeco_ana_260_seq = cms.Sequence(hltHM220*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
