import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *
from RiceHIG.V0Analysis.SelectedVertex_cfi import *

corr_ana_pp = corr_ana.clone(

#  VertexCollection = cms.string('selectedVertex'),

  pttrgmin = cms.vdouble(0.0, 0.2, 0.4, 0.6, 0.8, 1.1, 1.5, 2.0, 2.7, 4.0, 5.6, 9.0),
  pttrgmax = cms.vdouble(0.2, 0.4, 0.6, 0.8, 1.1, 1.5, 2.0, 2.7, 4.0, 5.6, 9.0, 12.0),

  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(3.0),

  rhomax = cms.double(0.5),

  xvtxcenter = cms.double(0.1),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(-0.4),

  zvtxmin = cms.double(-100),
  zvtxmax = cms.double(100),
  zvtxbin = cms.double(200),

  EffFileName = cms.string('')
)

corr_ana_pp_ks_sig = corr_ana_pp.clone(

# v1
#  pttrgmin = cms.vdouble(0.0, 0.2, 0.4, 0.6, 0.8, 1.1, 1.5, 2.0, 2.7, 4.0, 5.6, 9.0),
#  pttrgmax = cms.vdouble(0.2, 0.4, 0.6, 0.8, 1.1, 1.5, 2.0, 2.7, 4.0, 5.6, 9.0, 12.0),

# v2
  pttrgmin = cms.vdouble(0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0, 3.5, 4.5, 6.0, 9.0),
  pttrgmax = cms.vdouble(0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0, 3.5, 4.5, 6.0, 9.0, 12.0),

### n 105-1000, v1
#  massmean_trg = cms.vdouble(0.49767, 0.497058, 0.497299, 0.497527, 0.497613, 0.497672, 0.497633, 0.497536, 0.497469, 0.497427, 0.497455, 0.497481),
#  massmean_ass = cms.vdouble(0.49767, 0.497058, 0.497299, 0.497527, 0.497613, 0.497672, 0.497633, 0.497536, 0.497469, 0.497427, 0.497455, 0.497481),
#  masswidth_trg = cms.vdouble(0.00690711, 0.00775885, 0.00843139, 0.00778067, 0.00773932, 0.00820891, 0.008909, 0.00964192, 0.00936503, 0.00805014, 0.00717304, 0.00824782),
#  masswidth_ass = cms.vdouble(0.00690711, 0.00775885, 0.00843139, 0.00778067, 0.00773932, 0.00820891, 0.008909, 0.00964192, 0.00936503, 0.00805014, 0.00717304, 0.00824782),

### n 120-150, v2
  massmean_trg = cms.vdouble(0.49754, 0.49688, 0.497273, 0.497579, 0.497653, 0.497684, 0.497677, 0.497591, 0.49753, 0.497527, 0.497449, 0.497424, 0.497504, 0.497347, 0.497271),
  massmean_ass = cms.vdouble(0.49754, 0.49688, 0.497273, 0.497579, 0.497653, 0.497684, 0.497677, 0.497591, 0.49753, 0.497527, 0.497449, 0.497424, 0.497504, 0.497347, 0.497271),
  masswidth_trg = cms.vdouble(0.00720197, 0.00796063, 0.00760381, 0.00727464, 0.00681827, 0.00846351, 0.00673144, 0.00655313, 0.00616414, 0.00639074, 0.00631258, 0.00661941, 0.00749656, 0.0115225, 0.00776977),
  masswidth_ass = cms.vdouble(0.00720197, 0.00796063, 0.00760381, 0.00727464, 0.00681827, 0.00846351, 0.00673144, 0.00655313, 0.00616414, 0.00639074, 0.00631258, 0.00661941, 0.00749656, 0.0115225, 0.00776977),

  TriggerID = cms.string('Kshort'),

  IsV0SignalTrg = cms.bool(True),
  IsV0BkgTrg = cms.bool(False)
)

corr_ana_pp_ks_bkg = corr_ana_pp_ks_sig.clone(

  IsV0SignalTrg = cms.bool(False),
  IsV0BkgTrg = cms.bool(True)
)  

corr_ana_pp_la_sig = corr_ana_pp_ks_sig.clone(

  TriggerID = cms.string('Lambda'),

### n 105-1000, v1
#  massmean_trg = cms.vdouble(1.11575, 1.11649, 1.11665, 1.11621, 1.11604, 1.11591, 1.1159, 1.11591, 1.11589, 1.1158, 1.11579, 1.11577),
#  massmean_ass = cms.vdouble(1.11575, 1.11649, 1.11665, 1.11621, 1.11604, 1.11591, 1.1159, 1.11591, 1.11589, 1.1158, 1.11579, 1.11577),
#  masswidth_trg = cms.vdouble(0.0294431, 0.0174228, 0.00331539, 0.00336532, 0.00289146, 0.00274326, 0.00287908, 0.00272849, 0.00303222, 0.00313341, 0.00305282, 0.00321509),
#  masswidth_ass = cms.vdouble(0.0294431, 0.0174228, 0.00331539, 0.00336532, 0.00289146, 0.00274326, 0.00287908, 0.00272849, 0.00303222, 0.00313341, 0.00305282, 0.00321509)

### n 120-150, v2
  massmean_trg = cms.vdouble(1.12, 1.11561, 1.11682, 1.11618, 1.11608, 1.11593, 1.11589, 1.11589, 1.11589, 1.11598, 1.11589, 1.11584, 1.1158, 1.11572, 1.11609),
  massmean_ass = cms.vdouble(1.12, 1.11561, 1.11682, 1.11618, 1.11608, 1.11593, 1.11589, 1.11589, 1.11589, 1.11598, 1.11589, 1.11584, 1.1158, 1.11572, 1.11609),
  masswidth_trg = cms.vdouble(0.0295279, 0.0160316, 0.00326359, 0.00344954, 0.00283513, 0.00273531, 0.00266601, 0.0027186, 0.00273123, 0.00296408, 0.00300367, 0.003031, 0.00282828, 0.00330092, 0.00308034),
  masswidth_ass = cms.vdouble(0.0295279, 0.0160316, 0.00326359, 0.00344954, 0.00283513, 0.00273531, 0.00266601, 0.0027186, 0.00273123, 0.00296408, 0.00300367, 0.003031, 0.00282828, 0.00330092, 0.00308034)
)

corr_ana_pp_la_bkg = corr_ana_pp_la_sig.clone(

  IsV0SignalTrg = cms.bool(False),
  IsV0BkgTrg = cms.bool(True)
)

corr_ana_HI = corr_ana.clone(
#  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  rhomin = cms.double(0.0),
  rhomax = cms.double(0.5),
  xvtxcenter = cms.double(0.077),
  yvtxcenter = cms.double(0.037),
  zvtxcenter = cms.double(-0.54),

#  pttrgmin = cms.vdouble(0.3, 0.5, 0.75, 1.0, 1.5, 2.0, 2.5),
#  pttrgmax = cms.vdouble(0.5, 0.75, 1.0, 1.5, 2.0, 2.5, 3.0),
#  ptassmin = cms.vdouble(0.3, 0.5, 0.75, 1.0, 1.5, 2.0, 2.5),
#  ptassmax = cms.vdouble(0.5, 0.75, 1.0, 1.5, 2.0, 2.5, 3.0),

  pttrgmin = cms.vdouble(0.0),
  pttrgmax = cms.vdouble(20.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(20.0),

  IsHarmonics = cms.bool(False),
  IsHarmonicsEta1Eta2 = cms.bool(False),
  IsFullMatrix = cms.bool(False),
  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('')
)

corr_ana_HI_hf = corr_ana_HI.clone(
  pttrgmin = cms.vdouble(0.0),
  pttrgmax = cms.vdouble(10000.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(10000.0),

  etatrgmin = cms.double(-5.0),
  etatrgmax = cms.double(-4.0),
  etaassmin = cms.double(4.0),
  etaassmax = cms.double(5.0),

  IsPtWeightTrg = cms.bool(True),
  IsPtWeightAss = cms.bool(True),

  TriggerID = cms.string('CaloTower'),
  AssociateID = cms.string('CaloTower'),
)

corr_ana_HI_highPt = corr_ana_HI.clone(
  IsHarmonics = cms.bool(False),
  pttrgmin = cms.vdouble(12.0),
  pttrgmax = cms.vdouble(10000.0),
  ptassmin = cms.vdouble(0.5,1.0,2.0,3.0,4.0,6.0,8.0),
  ptassmax = cms.vdouble(1.0,2.0,3.0,4.0,6.0,8.0,12.0)
)

corr_ana_pPb = corr_ana.clone(
  rhomax = cms.double(0.5),

  IsFullMatrix = cms.bool(False),

  pttrgmin = cms.vdouble(1.0, 2.0, 4.0, 6.0),
  pttrgmax = cms.vdouble(2.0, 4.0, 6.0, 12.0),
  ptassmin = cms.vdouble(1.0, 2.0, 4.0, 6.0),
  ptassmax = cms.vdouble(2.0, 4.0, 6.0, 12.0),

#  EffFileName = cms.string('')
)

corr_ana_pPb_TrkCalo = corr_ana.clone(
  rhomax = cms.double(0.5),

  IsFullMatrix = cms.bool(False),

  pttrgmin = cms.vdouble(12.0),
  pttrgmax = cms.vdouble(100.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(100.0),

  AssociateID = cms.string('CaloTower'),

  etatrgmin = cms.double(-2.4),
  etatrgmax = cms.double(0.0),
  etaassmin = cms.double(3.0),
  etaassmax = cms.double(5.0),

  EffFileName = cms.string('')
)
