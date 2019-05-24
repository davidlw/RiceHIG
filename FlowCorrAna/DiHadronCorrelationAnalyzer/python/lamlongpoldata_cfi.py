import FWCore.ParameterSet.Config as cms

corr_ana = cms.EDAnalyzer('LamLongPolDataAnalyzer',

  centralityBinLabel = cms.InputTag("centralityBin","HFtowers"), 
  centralitySrc = cms.InputTag("hiCentrality"),

  TrgTrackCollection = cms.InputTag('generalTracks'),
  VertexCollection = cms.InputTag('offlinePrimaryVertices'),
  GenParticleCollection = cms.InputTag('genParticles'),
  V0CandidateCollection = cms.InputTag('generalV0CandidatesNew'),
  pfCandidateCollection = cms.InputTag('particleFlowTmp'),

  TriggerID = cms.string('Lambda'),
  AssociateID = cms.string('CaloTower'),

  NEtaBins = cms.int32(32),
  NPhiBins = cms.int32(32),
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
  xvtxcenter = cms.double(0.0),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(0.0),
  etatrgmin = cms.double(-2.4),
  etatrgmax = cms.double(2.4),
  etaassmin = cms.double(3),
  etaassmax = cms.double(5),
  pttrgmin = cms.vdouble(0.7,1.0,2.0,3.0,5.0),
  pttrgmax = cms.vdouble(1.0,2.0,3.0,5.0,10.0),
<<<<<<< HEAD
  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(10.0),
=======
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(1000.0),
>>>>>>> a0623bf651233e590d34b2e295af2623a4f87153
  etamultmin = cms.double(-2.4),
  etamultmax = cms.double(2.4),
  chargeasymmin = cms.double(-9999.9),
  chargeasymmax = cms.double(9999.9),
  nvtxmax = cms.int32(9999),
  etacms = cms.double(0.0),
  ptmultmin = cms.double(0.4),
  ptmultmax = cms.double(10000),
  runmin = cms.int32(-1),
  runmax = cms.int32(-1),

  mass_trg = cms.double(0.140),
  mass_ass = cms.double(0.140),
  massmean_trg = cms.vdouble(1.116,1.116,1.116,1.116,1.116),
  massmean_ass = cms.vdouble(99999.0),
  masswidth_trg = cms.vdouble(0.2,0.2,0.2,0.2,0.2),
  masswidth_ass = cms.vdouble(99999.0),
  genpdgId_trg = cms.int32(3122),
  genpdgId_ass = cms.int32(-999999),
  isstable_trg = cms.bool(False),
  isstable_ass = cms.bool(True),
  ischarge_trg = cms.bool(False),
  ischarge_ass = cms.bool(True),

  IsGenMult = cms.bool(False),
  IsVtxSel = cms.bool(True),
  IsCorr = cms.bool(True),
  IsHI = cms.bool(False),
  IsV0SignalTrg = cms.bool(True),
  IsV0SignalAss = cms.bool(False),
  IsV0BkgTrg = cms.bool(False),
  IsV0BkgAss = cms.bool(False),
  IsHarmonics = cms.bool(True),
  IsHarmonicsEta1Eta2 = cms.bool(False),
  IsFullMatrix = cms.bool(True),
  IsPtWeightTrg = cms.bool(False),
<<<<<<< HEAD
  IsPtWeightAss = cms.bool(False),
=======
  IsPtWeightAss = cms.bool(True),
>>>>>>> a0623bf651233e590d34b2e295af2623a4f87153
  IsTrgEtaCutAbs = cms.bool(False),
  IsAssEtaCutAbs = cms.bool(True),
  IsHITrkQuality = cms.bool(False),
  IsPPTrkQuality = cms.bool(True),
  IsDebug = cms.bool(False),
  IsInvMass = cms.bool(False),
  IsEventEngineer = cms.bool(False),
  IsDSGenEvt = cms.bool(False),
  IsCheckTrgV0Dau = cms.bool(True),
  IsCheckAssV0Dau = cms.bool(False),
  IsBoostRestFrameV0 = cms.bool(True),

#  EffFileName = cms.string('TrackCorrections_HIJING_538_OFFICIAL_Mar24.root'),
  EffFileName = cms.string(''),
  EffHistName = cms.string('rTotalEff3D'),
  EtaPhiFileName = cms.string('')
)
