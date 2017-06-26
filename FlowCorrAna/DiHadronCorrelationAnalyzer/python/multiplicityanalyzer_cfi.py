import FWCore.ParameterSet.Config as cms

mult_ana = cms.EDAnalyzer('MultiplicityAnalyzer',

  TrgTrackCollection = cms.InputTag('generalTracks'),
  VertexCollection = cms.InputTag('offlinePrimaryVertices'),
  GenParticleCollection = cms.InputTag('genParticles'),

  zvtxmin = cms.double(-150),
  zvtxmax = cms.double(150),
  zvtxbin = cms.double(300),
  rhomin = cms.double(0.0),
  rhomax = cms.double(0.5),
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),
  etamultmin = cms.double(-2.4),
  etamultmax = cms.double(2.4),
  chargeasymmin = cms.double(-9999.9),
  chargeasymmax = cms.double(9999.9),
  nvtxmax = cms.int32(9999),
  ptmultmin = cms.double(0.4),
  ptmultmax = cms.double(10000),

  IsGenMult = cms.bool(True),
  IsVtxSel = cms.bool(True),
  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(True),

  EffFileName = cms.string('TrackCorrections_HIJING_538_OFFICIAL_Mar24.root')
)
