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

epptdecomatrix_ana_pp = epptdecomatrix_ana.clone(
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),

  pttrgmin = cms.vdouble(0.3,0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15),
  pttrgmax = cms.vdouble(0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15,20),
  ptassmin = cms.vdouble(0.3,0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15),
  ptassmax = cms.vdouble(0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15,20),

  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(True),

  EffFileName = cms.string(''),
  EffHistName = cms.string('Eff3D'),

  FakFileName = cms.string(''),
  FakHistName = cms.string('Fak3D'),

  AssociateID = cms.string('')
)

epptdecomatrix_ana_pp_gen = epptdecomatrix_ana_pp.clone(

  TriggerID = cms.string('GenParticle')

)
