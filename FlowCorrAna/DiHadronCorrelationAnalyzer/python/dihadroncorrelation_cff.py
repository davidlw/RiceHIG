import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *
from RiceHIG.V0Analysis.SelectedVertex_cfi import *

corr_ana_pp = corr_ana.clone(

  VertexCollection = cms.string('selectedVertex'),

  pttrgmin = cms.vdouble(0.0, 0.4, 0.7, 1.1, 1.7, 2.7, 4.0, 5.6),
  pttrgmax = cms.vdouble(0.4, 0.7, 1.1, 1.7, 2.7, 4.0, 5.6, 9.0),

  ptassmin = cms.vdouble(0.3),
  ptassmax = cms.vdouble(3.0),

  rhomax = cms.double(0.5),

  xvtxcenter = cms.double(0.1),
  yvtxcenter = cms.double(0.0),
  zvtxcenter = cms.double(-0.4),

  zvtxmin = cms.double(-100),
  zvtxmax = cms.double(100),
  zvtxbin = cms.double(200),

  EffFileName = cms.string('trkEff_pp_all_42X_origin.root')
)

corr_ana_pp_ks_sig = corr_ana_pp.clone(
  
  pttrgmin = cms.vdouble(0.0, 0.4, 0.7, 1.1, 1.7, 2.7, 4.0, 5.6),
  pttrgmax = cms.vdouble(0.4, 0.7, 1.1, 1.7, 2.7, 4.0, 5.6, 9.0),

### n 10-20, v40
#  massmean_trg = cms.vdouble(0.497371, 0.497417, 0.497706, 0.49776, 0.497645, 0.497593, 0.497454, 0.497488),
#  massmean_ass = cms.vdouble(0.497371, 0.497417, 0.497706, 0.49776, 0.497645, 0.497593, 0.497454, 0.497488),
#  masswidth_trg = cms.vdouble(0.00764028, 0.00758532, 0.00763788, 0.00845018, 0.00953448, 0.00726748, 0.00761666, 0.0077134),
#  masswidth_ass = cms.vdouble(0.00764028, 0.00758532, 0.00763788, 0.00845018, 0.00953448, 0.00726748, 0.00761666, 0.0077134),

### n 10-20, v38
#  massmean_trg = cms.vdouble(0.497371, 0.497417, 0.497706, 0.49776, 0.497805, 0.497578, 0.497577, 0.497413),
#  massmean_ass = cms.vdouble(0.497371, 0.497417, 0.497706, 0.49776, 0.497805, 0.497578, 0.497577, 0.497413),
#  masswidth_trg = cms.vdouble(0.00764028, 0.00758532, 0.00763788, 0.00845018, 0.00764253, 0.00649754, 0.00743083, 0.00746865),
#  masswidth_ass = cms.vdouble(0.00764028, 0.00758532, 0.00763788, 0.00845018, 0.00764253, 0.00649754, 0.00743083, 0.00746865),

### n 110-150, v38
#  massmean_trg = cms.vdouble(0.497756, 0.497334, 0.497584, 0.497616, 0.497583, 0.497465, 0.497563, 0.497482),
#  massmean_ass = cms.vdouble(0.497756, 0.497334, 0.497584, 0.497616, 0.497583, 0.497465, 0.497563, 0.497482),
#  masswidth_trg = cms.vdouble(0.00710591, 0.00767582, 0.00800011, 0.00904199, 0.00857348, 0.00634806, 0.00699872, 0.00672812),
#  masswidth_ass = cms.vdouble(0.00710591, 0.00767582, 0.00800011, 0.00904199, 0.00857348, 0.00634806, 0.00699872, 0.00672812),

### n 110-150, v40
  massmean_trg = cms.vdouble(0.497756, 0.497334, 0.497584, 0.497616, 0.49754, 0.497551, 0.497479, 0.497516),
  massmean_ass = cms.vdouble(0.497756, 0.497334, 0.497584, 0.497616, 0.49754, 0.497551, 0.497479, 0.497516),
  masswidth_trg = cms.vdouble(0.00710591, 0.00767582, 0.00800011, 0.00904199, 0.00928984, 0.00717466, 0.00714707, 0.00729814),
  masswidth_ass = cms.vdouble(0.00710591, 0.00767582, 0.00800011, 0.00904199, 0.00928984, 0.00717466, 0.00714707, 0.00729814),

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

### n 10-20, v38
#  massmean_trg = cms.vdouble(1.11692, 1.11668, 1.1162, 1.11591, 1.11591, 1.11592, 1.11582, 1.11578),
#  massmean_ass = cms.vdouble(1.11692, 1.11668, 1.1162, 1.11591, 1.11591, 1.11592, 1.11582, 1.11578),
#  masswidth_trg = cms.vdouble(0.007436, 0.00330545, 0.00322766, 0.00306866, 0.00292984, 0.00322157, 0.00315324, 0.00345762),
#  masswidth_ass = cms.vdouble(0.007436, 0.00330545, 0.00322766, 0.00306866, 0.00292984, 0.00322157, 0.00315324, 0.00345762)

### n 10-20, v40
#  massmean_trg = cms.vdouble(1.11692, 1.11668, 1.1162, 1.11591, 1.11591, 1.11586, 1.1158, 1.11584),
#  massmean_ass = cms.vdouble(1.11692, 1.11668, 1.1162, 1.11591, 1.11591, 1.11586, 1.1158, 1.11584),
#  masswidth_trg = cms.vdouble(0.007436, 0.00330545, 0.00322766, 0.00306866, 0.00293087, 0.00303375, 0.00318566, 0.00476279),
#  masswidth_ass = cms.vdouble(0.007436, 0.00330545, 0.00322766, 0.00306866, 0.00293087, 0.00303375, 0.00318566, 0.00476279)

### n 110-150, v38
#  massmean_trg = cms.vdouble(1.11624, 1.11642, 1.11618, 1.11591, 1.11589, 1.11588, 1.11587, 1.11583),
#  massmean_ass = cms.vdouble(1.11624, 1.11642, 1.11618, 1.11591, 1.11589, 1.11588, 1.11587, 1.11583),
#  masswidth_trg = cms.vdouble(0.00326117, 0.0041025, 0.00376517, 0.00314638, 0.00291154, 0.00328918, 0.0034094, 0.00294318),
#  masswidth_ass = cms.vdouble(0.00326117, 0.0041025, 0.00376517, 0.00314638, 0.00291154, 0.00328918, 0.0034094, 0.00294318)

### n 110-150, v40
  massmean_trg = cms.vdouble(1.11624, 1.11642, 1.11618, 1.11591, 1.11589, 1.11587, 1.11585, 1.11574),
  massmean_ass = cms.vdouble(1.11624, 1.11642, 1.11618, 1.11591, 1.11589, 1.11587, 1.11585, 1.11574),
  masswidth_trg = cms.vdouble(0.00326117, 0.0041025, 0.00376517, 0.00314638, 0.00289683, 0.00336975, 0.00296136, 0.00336001),
  masswidth_ass = cms.vdouble(0.00326117, 0.0041025, 0.00376517, 0.00314638, 0.00289683, 0.00336975, 0.00296136, 0.00336001)
)

corr_ana_pp_la_bkg = corr_ana_pp_la_sig.clone(

  IsV0SignalTrg = cms.bool(False),
  IsV0BkgTrg = cms.bool(True)
)

corr_ana_HI = corr_ana.clone(
#  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  rhomin = cms.double(0.0),
  rhomax = cms.double(0.02),
  xvtxcenter = cms.double(0.077),
  yvtxcenter = cms.double(0.037),
  zvtxcenter = cms.double(-0.54),

  pttrgmin = cms.vdouble(0.3, 0.5, 0.75, 1.0, 1.5, 2.0, 2.5),
  pttrgmax = cms.vdouble(0.5, 0.75, 1.0, 1.5, 2.0, 2.5, 3.0),
  ptassmin = cms.vdouble(0.3, 0.5, 0.75, 1.0, 1.5, 2.0, 2.5),
  ptassmax = cms.vdouble(0.5, 0.75, 1.0, 1.5, 2.0, 2.5, 3.0),

  IsHarmonics = cms.bool(True),
  IsHarmonicsEta1Eta2 = cms.bool(True),
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
