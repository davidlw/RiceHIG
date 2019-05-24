import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.scalarprodnew_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

scalarprod_ana_hp = scalarprod_ana.clone(
  TriggerID = cms.string('TrackP')
)

scalarprod_ana_hm = scalarprod_ana.clone(
  TriggerID = cms.string('TrackM')
)

scalarprod_ana_HI = scalarprod_ana.clone(
  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('genParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),
)

scalarprod_ana_gen_trkhfp = scalarprod_ana.clone(
  TriggerID = cms.string('Generator'),
  AssociateID = cms.string('Generator'),

  etatrgmin = cms.double(-1.),
  etatrgmax = cms.double(1.),
  etaassmin = cms.double(3.),
  etaassmax = cms.double(5.),
  pttrgmin = cms.vdouble(0.3),
  pttrgmax = cms.vdouble(10.0),
  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(10.0),

  IsGenMult = cms.bool(True),
  IsVtxSel = cms.bool(False),

  IsPtWeightTrg = cms.bool(False),
  IsPtWeightAss = cms.bool(False),
  IsTrgEtaCutAbs = cms.bool(False),
  IsAssEtaCutAbs = cms.bool(False)
)

scalarprod_ana_gen_trkhfm = scalarprod_ana_gen_trkhfp.clone(
  etaassmin = cms.double(-5.0),
  etaassmax = cms.double(-3.0)
)

scalarprod_ana_gen_hfphfm = scalarprod_ana_gen_trkhfp.clone(
  etaassmin = cms.double(-5.0),
  etaassmax = cms.double(-3.0),
  etatrgmin = cms.double(3.0),
  etatrgmax = cms.double(5.0),

  ischarge_trg = cms.bool(False)
)