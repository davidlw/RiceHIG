import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.ptspectra_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *
from RiceHIG.V0Analysis.SelectedVertex_cfi import *

ptspectra_ana_N010 = ptspectra_ana.clone()
ptspectra_ana_N010.nmin = cms.int32(0)
ptspectra_ana_N010.nmax = cms.int32(10)
ptspectra_ana_N1020 = ptspectra_ana.clone()
ptspectra_ana_N1020.nmin = cms.int32(10)
ptspectra_ana_N1020.nmax = cms.int32(20)
ptspectra_ana_N2030 = ptspectra_ana.clone()
ptspectra_ana_N2030.nmin = cms.int32(20)
ptspectra_ana_N2030.nmax = cms.int32(30)
ptspectra_ana_N3040 = ptspectra_ana.clone()
ptspectra_ana_N3040.nmin = cms.int32(30)
ptspectra_ana_N3040.nmax = cms.int32(40)
ptspectra_ana_N4050 = ptspectra_ana.clone()
ptspectra_ana_N4050.nmin = cms.int32(40)
ptspectra_ana_N4050.nmax = cms.int32(50)
ptspectra_ana_N5060 = ptspectra_ana.clone()
ptspectra_ana_N5060.nmin = cms.int32(50)
ptspectra_ana_N5060.nmax = cms.int32(60)
ptspectra_ana_N6070 = ptspectra_ana.clone()
ptspectra_ana_N6070.nmin = cms.int32(60)
ptspectra_ana_N6070.nmax = cms.int32(70)
ptspectra_ana_N7080 = ptspectra_ana.clone()
ptspectra_ana_N7080.nmin = cms.int32(70)
ptspectra_ana_N7080.nmax = cms.int32(80)
ptspectra_ana_N80100 = ptspectra_ana.clone()
ptspectra_ana_N80100.nmin = cms.int32(80)
ptspectra_ana_N80100.nmax = cms.int32(100)
ptspectra_ana_N100120 = ptspectra_ana.clone()
ptspectra_ana_N100120.nmin = cms.int32(100)
ptspectra_ana_N100120.nmax = cms.int32(120)
ptspectra_ana_N120135 = ptspectra_ana.clone()
ptspectra_ana_N120135.nmin = cms.int32(120)
ptspectra_ana_N120135.nmax = cms.int32(135)
ptspectra_ana_N135150 = ptspectra_ana.clone()
ptspectra_ana_N135150.nmin = cms.int32(135)
ptspectra_ana_N135150.nmax = cms.int32(150)
ptspectra_ana_N150160 = ptspectra_ana.clone()
ptspectra_ana_N150160.nmin = cms.int32(150)
ptspectra_ana_N150160.nmax = cms.int32(160)
ptspectra_ana_N160185 = ptspectra_ana.clone()
ptspectra_ana_N160185.nmin = cms.int32(160)
ptspectra_ana_N160185.nmax = cms.int32(185)
ptspectra_ana_N185210 = ptspectra_ana.clone()
ptspectra_ana_N185210.nmin = cms.int32(185)
ptspectra_ana_N185210.nmax = cms.int32(210)
ptspectra_ana_N210230 = ptspectra_ana.clone()
ptspectra_ana_N210230.nmin = cms.int32(210)
ptspectra_ana_N210230.nmax = cms.int32(230)
ptspectra_ana_N230250 = ptspectra_ana.clone()
ptspectra_ana_N230250.nmin = cms.int32(230)
ptspectra_ana_N230250.nmax = cms.int32(250)
ptspectra_ana_N250270 = ptspectra_ana.clone()
ptspectra_ana_N250270.nmin = cms.int32(250)
ptspectra_ana_N250270.nmax = cms.int32(270)
ptspectra_ana_N270300 = ptspectra_ana.clone()
ptspectra_ana_N270300.nmin = cms.int32(270)
ptspectra_ana_N270300.nmax = cms.int32(300)
ptspectra_ana_N300330 = ptspectra_ana.clone()
ptspectra_ana_N300330.nmin = cms.int32(300)
ptspectra_ana_N300330.nmax = cms.int32(330)

ptspectra_ana_N330350 = ptspectra_ana.clone()
ptspectra_ana_N330350.nmin = cms.int32(330)
ptspectra_ana_N330350.nmax = cms.int32(350)
ptspectra_ana_N350370 = ptspectra_ana.clone()
ptspectra_ana_N350370.nmin = cms.int32(350)
ptspectra_ana_N350370.nmax = cms.int32(370)
ptspectra_ana_N370390 = ptspectra_ana.clone()
ptspectra_ana_N370390.nmin = cms.int32(370)
ptspectra_ana_N370390.nmax = cms.int32(390)
ptspectra_ana_N390420 = ptspectra_ana.clone()
ptspectra_ana_N390420.nmin = cms.int32(390)
ptspectra_ana_N390420.nmax = cms.int32(420)
ptspectra_ana_N420500 = ptspectra_ana.clone()
ptspectra_ana_N420500.nmin = cms.int32(420)
ptspectra_ana_N420500.nmax = cms.int32(500)

ptspectra_ana_N330360 = ptspectra_ana.clone()
ptspectra_ana_N330360.nmin = cms.int32(330)
ptspectra_ana_N330360.nmax = cms.int32(360)
ptspectra_ana_N360400 = ptspectra_ana.clone()
ptspectra_ana_N360400.nmin = cms.int32(360)
ptspectra_ana_N360400.nmax = cms.int32(400)
ptspectra_ana_N400500 = ptspectra_ana.clone()
ptspectra_ana_N400500.nmin = cms.int32(400)
ptspectra_ana_N400500.nmax = cms.int32(500)
ptspectra_ana_N500800 = ptspectra_ana.clone()
ptspectra_ana_N500800.nmin = cms.int32(500)
ptspectra_ana_N500800.nmax = cms.int32(800)

ptspectra_ana_pp = ptspectra_ana.clone(

#  VertexCollection = cms.string('selectedVertex'),

# 14-002
#  pttrgmin = cms.vdouble(0.0, 0.2, 0.4, 0.6, 0.8, 1.1, 1.5, 2.0, 2.7, 4.0, 5.6, 9.0),
#  pttrgmax = cms.vdouble(0.2, 0.4, 0.6, 0.8, 1.1, 1.5, 2.0, 2.7, 4.0, 5.6, 9.0, 12.0),

  pttrgmin = cms.vdouble(0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0, 3.5, 4.5, 6.0, 9.0),
  pttrgmax = cms.vdouble(0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0, 3.5, 4.5, 6.0, 9.0, 12.0),

#  pttrgmin = cms.vdouble(0.0, 0.4, 0.7, 1.1, 1.7, 2.7, 4.0, 5.6),
#  pttrgmax = cms.vdouble(0.4, 0.7, 1.1, 1.7, 2.7, 4.0, 5.6, 9.0),

  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(3.0),

  rhomax = cms.double(0.5),

  xvtxcenter = cms.double(0.1),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(-0.4),

  zvtxmin = cms.double(-150),
  zvtxmax = cms.double(150),
  zvtxbin = cms.double(300),

#  EffFileName = cms.string('trkEff_pp_all_74X_origin.root')
  EffFileName = cms.string('pp_dijet_NTT_5TeV.root')
)

ptspectra_ana_pp_ks_sig = ptspectra_ana_pp.clone(

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

ptspectra_ana_pp_ks_bkg = ptspectra_ana_pp_ks_sig.clone(

  IsV0SignalTrg = cms.bool(False),
  IsV0BkgTrg = cms.bool(True)
)  

ptspectra_ana_pp_la_sig = ptspectra_ana_pp_ks_sig.clone(

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

ptspectra_ana_pp_la_bkg = ptspectra_ana_pp_la_sig.clone(

  IsV0SignalTrg = cms.bool(False),
  IsV0BkgTrg = cms.bool(True)
)

ptspectra_ana_HI = ptspectra_ana.clone(
#  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
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
  pttrgmax = cms.vdouble(10000.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(10000.0),

  IsHarmonics = cms.bool(False),
  IsHarmonicsEta1Eta2 = cms.bool(False),
  IsFullMatrix = cms.bool(False),
  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('EffCorrectionsPixel_NTT_pt_0_10_v2.root'),
  EffHistName = cms.string('rTotalEff3D')
)

ptspectra_ana_HI_hf = ptspectra_ana_HI.clone(
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

ptspectra_ana_HI_highPt = ptspectra_ana_HI.clone(
  IsHarmonics = cms.bool(False),
  pttrgmin = cms.vdouble(12.0),
  pttrgmax = cms.vdouble(10000.0),
  ptassmin = cms.vdouble(0.5,1.0,2.0,3.0,4.0,6.0,8.0),
  ptassmax = cms.vdouble(1.0,2.0,3.0,4.0,6.0,8.0,12.0)
)

ptspectra_ana_pPb = ptspectra_ana.clone(
  rhomax = cms.double(0.5),

  IsFullMatrix = cms.bool(False),

  pttrgmin = cms.vdouble(0.3, 0.5, 1.0, 2.0, 4.0, 6.0),
  pttrgmax = cms.vdouble(0.5, 1.0, 2.0, 4.0, 6.0, 12.0),
  ptassmin = cms.vdouble(0.3, 0.5, 1.0, 2.0, 4.0, 6.0),
  ptassmax = cms.vdouble(0.5, 1.0, 2.0, 4.0, 6.0, 12.0),

#  EffFileName = cms.string('')
)

ptspectra_ana_pPb_TrkCalo = ptspectra_ana.clone(
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
