import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epetadeco_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

epetadeco_ana_HI_hfp = epetadeco_ana.clone(
#  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  etaassmin = cms.double(4.4),
  etaassmax = cms.double(5.0),
  pttrgmin = cms.vdouble(8.0),
  pttrgmax = cms.vdouble(10000.0),

#  ptassmin = cms.vdouble(1.0),

#  IsPtWeightTrg = cms.bool(False),

#  EffFileName = cms.string('trkEffNew2012_HI_pixeltracks_tmp.root')
  EffFileName = cms.string('')
)

epetadeco_ana_HI_nocorr = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(-1),
  centmax = cms.int32(-1),
  IsCorr = cms.bool(False)
)

epetadeco_ana_HI_hfm = epetadeco_ana_HI_hfp.clone(
  etaassmin = cms.double(-5.0),
  etaassmax = cms.double(-4.4)
)

epetadeco_ana_HI_hfp_cent002 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(1100),
  centmax = cms.int32(10000)
)

epetadeco_ana_HI_hfm_cent002 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(1100),
  centmax = cms.int32(10000)
)

epetadeco_ana_HI_hfp_cent05 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(0),
  centmax = cms.int32(10)
)

epetadeco_ana_HI_hfm_cent05 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(0),
  centmax = cms.int32(10)
)

epetadeco_ana_HI_hfp_cent510 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(10),
  centmax = cms.int32(20)
)

epetadeco_ana_HI_hfm_cent510 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(10),
  centmax = cms.int32(20)
)

epetadeco_ana_HI_hfp_cent1020 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(20),
  centmax = cms.int32(40)
)

epetadeco_ana_HI_hfm_cent1020 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(20),
  centmax = cms.int32(40)
)

epetadeco_ana_HI_hfp_cent2030 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(40),
  centmax = cms.int32(60)
)

epetadeco_ana_HI_hfm_cent2030 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(40),
  centmax = cms.int32(60)
)

epetadeco_ana_HI_hfp_cent3040 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(60),
  centmax = cms.int32(80)
)

epetadeco_ana_HI_hfm_cent3040 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(60),
  centmax = cms.int32(80)
)

epetadeco_ana_HI_hfp_cent4050 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(80),
  centmax = cms.int32(100)
)

epetadeco_ana_HI_hfm_cent4050 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(80),
  centmax = cms.int32(100)
)

epetadeco_ana_HI_hfp_cent5060 = epetadeco_ana_HI_hfp.clone(
  centmin = cms.int32(100),
  centmax = cms.int32(120)
)

epetadeco_ana_HI_hfm_cent5060 = epetadeco_ana_HI_hfm.clone(
  centmin = cms.int32(100),
  centmax = cms.int32(120)
)

epetadeco_ana_pPb_hfp = epetadeco_ana.clone(
#  EffFileName = cms.string(''),

#  etacms = cms.double(-0.47),
#  etatrgmin = cms.double(-2.4),
#  etatrgmax = cms.double(2.4-0.47*2),

#  etacms = cms.double(0.47),
#  etatrgmin = cms.double(-2.4+0.47*2),
#  etatrgmax = cms.double(2.4),

#   nvtxmax = cms.int32(1),

#  ptassmin = cms.vdouble(0.3),

  etaassmin = cms.double(4.4),
  etaassmax = cms.double(5.0)
#  etaassmin = cms.double(4.0),
#  etaassmax = cms.double(5.2)

#  etaassmin = cms.double(3.46-0.16),
#  etaassmax = cms.double(4.26+0.04)
#  etaassmin = cms.double(-4.26-0.04),
#  etaassmax = cms.double(-3.46+0.16)
)
epetadeco_ana_pPb_hfm = epetadeco_ana.clone(
#  EffFileName = cms.string(''),

#  etacms = cms.double(-0.47),
#  etatrgmin = cms.double(-2.4),
#  etatrgmax = cms.double(2.4-0.47*2),

#  etacms = cms.double(0.47),
#  etatrgmin = cms.double(-2.4+0.47*2),
#  etatrgmax = cms.double(2.4),

#   nvtxmax = cms.int32(1),

#  ptassmin = cms.vdouble(0.3),

#  etaassmin = cms.double(4.0),
#  etaassmax = cms.double(5.0)
#  etaassmin = cms.double(-5.2),
#  etaassmax = cms.double(-4.4+0.2)
#  etaassmin = cms.double(4.4-0.2),
#  etaassmax = cms.double(5.2)

  etaassmin = cms.double(-5.0),
  etaassmax = cms.double(-4.4)
#  etaassmin = cms.double(-5.2),
#  etaassmax = cms.double(-4.0)
)

epetadeco_ana_seq = cms.Sequence(epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
epetadeco_ana_120150_seq = cms.Sequence(hltHM120150*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
epetadeco_ana_150185_seq = cms.Sequence(hltHM150185*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
epetadeco_ana_185220_seq = cms.Sequence(hltHM185220*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
epetadeco_ana_220260_seq = cms.Sequence(hltHM220*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
epetadeco_ana_260_seq = cms.Sequence(hltHM220*epetadeco_ana_pPb_hfp*epetadeco_ana_pPb_hfm)
