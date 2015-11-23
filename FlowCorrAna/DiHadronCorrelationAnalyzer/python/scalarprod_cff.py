import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.scalarprod_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

scalarprod_ana_HI = scalarprod_ana.clone(
  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('genParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),
)

scalarprod_ana_HI_hf = scalarprod_ana_HI.clone(

  TriggerID = cms.string('CaloTower'),
  AssociateID = cms.string('CaloTower'),

  IsPtWeightTrg = cms.bool(True),
  IsPtWeightAss = cms.bool(True),
  IsTrgEtaCutAbs = cms.bool(True),
  IsAssEtaCutAbs = cms.bool(True),

  ischarge_trg = cms.bool(False),
  ischarge_ass = cms.bool(False),

  etatrgmin = cms.double(3.0),
  etatrgmax = cms.double(5.0),
  etaassmin = cms.double(3.0),
  etaassmax = cms.double(5.0),
  pttrgmin = cms.vdouble(0.0),
  pttrgmax = cms.vdouble(10000.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(10000.0),
)
