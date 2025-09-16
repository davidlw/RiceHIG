import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epptdecomatrixnew_cfi import *

epptdecomatrixnew_ana_HI = epptdecomatrixnew_ana.clone(
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

epptdecomatrixnew_ana_PbPb2018 = epptdecomatrixnew_ana.clone(
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

epptdecomatrixnew_ana_PbPb2023 = epptdecomatrixnew_ana.clone(
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),

  rhomin = cms.double(0.0),
  rhomax = cms.double(1.0),
  
  pttrgmin = cms.vdouble(0.4,0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10,12,15),
  pttrgmax = cms.vdouble(0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.,12,15,20),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(0.0),
  
  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string(''),
  EffHistName = cms.string('hEff_3D'),

  FakFileName = cms.string(''),
  FakHistName = cms.string('hFak_3D'),

  AssociateID = cms.string('')
)

epptdecomatrixnew_ana_pp2023 = epptdecomatrixnew_ana.clone(
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),

  rhomin = cms.double(0.0),
  rhomax = cms.double(1.0),
  
  pttrgmin = cms.vdouble(0.3,0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10,12,15),
  pttrgmax = cms.vdouble(0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.,12,15,20),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(0.0),

  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(True),

  EffFileName = cms.string(''),
  EffHistName = cms.string('Eff3D'),

  FakFileName = cms.string(''),
  FakHistName = cms.string('Fak3D'),

  AssociateID = cms.string('')
)

epptdecomatrixnew_ana_pp2023_gen = epptdecomatrixnew_ana_pp2023.clone(

  TriggerID = cms.string('GenParticle')

)
