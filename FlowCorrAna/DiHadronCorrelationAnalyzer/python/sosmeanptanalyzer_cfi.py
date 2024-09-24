import FWCore.ParameterSet.Config as cms

sosmeanpt_ana = cms.EDAnalyzer('SoSMeanPtAnalyzer',

  TrgTrackCollection = cms.InputTag('generalTracks'),
  VertexCollection = cms.InputTag('offlinePrimaryVertices'),
  GenParticleCollection = cms.InputTag('genParticles'),
  centralitySrc = cms.InputTag("hiCentrality"),
  centralityBinLabel = cms.InputTag("centralityBin","HFtowers"),  

  pttrgmin = cms.vdouble(0.3),
  pttrgmax = cms.vdouble(3.0),
  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(3.0),

  xvtxcenter = cms.double(0.12),
  yvtxcenter = cms.double(-0.18),
  zvtxcenter = cms.double(-1.0),

  zvtxmin = cms.double(-150),
  zvtxmax = cms.double(150),
  zvtxbin = cms.double(300),
  rhomin = cms.double(0.0),
  rhomax = cms.double(0.5),

  etamultmin = cms.double(-2.4),
  etamultmax = cms.double(2.4),
  chargeasymmin = cms.double(-9999.9),
  chargeasymmax = cms.double(9999.9),
  nvtxmax = cms.int32(9999),
  ptmultmin = cms.double(0.4),
  ptmultmax = cms.double(10000),

  IsGenMult = cms.bool(False),
  IsVtxSel = cms.bool(True),
  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string(''),
  EffHistName = cms.string(''),
  FakFileName = cms.string(''),
  FakHistName = cms.string('')
)
