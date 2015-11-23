import FWCore.ParameterSet.Config as cms

scalarprod_ana = cms.EDAnalyzer('ScalarProdVnAnalyzer',

  centralityBinLabel = cms.InputTag("centralityBin","HFtowers"),

  TrgTrackCollection = cms.string('generalTracks'),
  VertexCollection = cms.string('offlinePrimaryVertices'),
  GenParticleCollection = cms.string('genParticles'),
  V0CandidateCollection = cms.string('generalV0CandidatesNew'),
  pfCandidateCollection = cms.string('particleFlowTmp'),

  TriggerID = cms.string('Track'),
  AssociateID = cms.string('CaloTower'),

  NEtaBins = cms.int32(40),
  NPhiBins = cms.int32(36),
  checksign = cms.int32(-1),

  nmin = cms.int32(-1),
  nmax = cms.int32(-1),
  centmin = cms.int32(-1),
  centmax = cms.int32(-1),
  zvtxmin = cms.double(-150),
  zvtxmax = cms.double(150),
  zvtxbin = cms.double(300),
  rhomin = cms.double(0.0),
  rhomax = cms.double(0.2),
  xvtxcenter = cms.double(0.077),
  yvtxcenter = cms.double(0.037),
  zvtxcenter = cms.double(-0.54),
  etatrgmin = cms.double(-1.0),
  etatrgmax = cms.double(1.0),
  etaassmin = cms.double(3.0),
  etaassmax = cms.double(5.0),
  pttrgmin = cms.vdouble(0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 14.0, 20.0),
  pttrgmax = cms.vdouble(1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0,14.0, 20.0, 100.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(10000.0),
  etamultmin = cms.double(-2.4),
  etamultmax = cms.double(2.4),
  chargeasymmin = cms.double(-9999.9),
  chargeasymmax = cms.double(9999.9),
  ptmultmin = cms.double(0.4),
  ptmultmax = cms.double(10000),
  runmin = cms.int32(-1),
  runmax = cms.int32(-1),
  nvtxmax = cms.int32(9999),
  etacms = cms.double(0.0),

  mass_trg = cms.double(0.140),
  mass_ass = cms.double(0.140),
  massmean_trg = cms.vdouble(99999.0),
  massmean_ass = cms.vdouble(99999.0),
  masswidth_trg = cms.vdouble(99999.0),
  masswidth_ass = cms.vdouble(99999.0),
  genpdgId_trg = cms.int32(-999999),
  genpdgId_ass = cms.int32(-999999),
  isstable_trg = cms.bool(True),
  isstable_ass = cms.bool(True),
  ischarge_trg = cms.bool(True),
  ischarge_ass = cms.bool(False),

  IsGenMult = cms.bool(False),
  IsVtxSel = cms.bool(True),
  IsCorr = cms.bool(True),
  IsHI = cms.bool(False),
  IsV0SignalTrg = cms.bool(False),
  IsV0SignalAss = cms.bool(False),
  IsV0BkgTrg = cms.bool(False),
  IsV0BkgAss = cms.bool(False),
  IsHarmonics = cms.bool(True),
  IsHarmonicsEta1Eta2 = cms.bool(False),
  IsFullMatrix = cms.bool(True),
  IsPtWeightTrg = cms.bool(False),
  IsPtWeightAss = cms.bool(True),
  IsTrgEtaCutAbs = cms.bool(False),
  IsAssEtaCutAbs = cms.bool(True),
  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(True),
  IsDebug = cms.bool(False),
  IsInvMass = cms.bool(False),
  IsEventEngineer = cms.bool(False),
  IsDSGenEvt = cms.bool(False),
  IsCheckTrgV0Dau = cms.bool(False),
  IsCheckAssV0Dau = cms.bool(False),
  IsBoostRestFrameV0 = cms.bool(False),

#  EffFileName = cms.string('TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
  EffFileName = cms.string(''),
  EtaPhiFileName = cms.string('')
)
