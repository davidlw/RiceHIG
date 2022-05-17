import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
process = cms.Process('ANASKIM',eras.Run2_2018_pp_on_AA)

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/himc/HINPbPbAutumn18DR/MinBias_Hydjet_Drum5F_2018_5p02TeV/AODSIM/NoPUmva98_103X_upgrade2018_realistic_HI_v11-v1/120000/411DF9D7-A2FF-AD42-8FE2-5D2396C0970D.root'),
   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '') 

# Add PbPb centrality
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')
process.hiCentrality.produceHFhits = False
process.hiCentrality.produceHFtowers = False
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceZDChits = False
process.hiCentrality.produceETmidRapidity = False
process.hiCentrality.producePixelhits = False
process.hiCentrality.produceTracks = False
process.hiCentrality.producePixelTracks = False
process.hiCentrality.reUseCentrality = True
process.hiCentrality.srcReUse = cms.InputTag("hiCentrality","","")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("")
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_HydjetDrum5F_v1032x02_mc"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])
#process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)
process.cent_seq = cms.Sequence(process.centralityBin)

# Add PbPb event plane
process.load("RecoHI.HiEvtPlaneAlgos.HiEvtPlane_cfi")
process.load("RecoHI.HiEvtPlaneAlgos.hiEvtPlaneFlat_cfi")
process.hiEvtPlane.trackTag = cms.InputTag("generalTracks")
process.hiEvtPlane.vertexTag = cms.InputTag("offlinePrimaryVerticesRecovery")
process.hiEvtPlane.loadDB = cms.bool(True)
process.hiEvtPlane.useNtrk = cms.untracked.bool(False)
process.hiEvtPlane.caloCentRef = cms.double(-1)
process.hiEvtPlane.caloCentRefWidth = cms.double(-1)
process.hiEvtPlaneFlat.caloCentRef = cms.double(-1)
process.hiEvtPlaneFlat.caloCentRefWidth = cms.double(-1)
process.hiEvtPlaneFlat.vertexTag = cms.InputTag("offlinePrimaryVerticesRecovery")
process.hiEvtPlaneFlat.useNtrk = cms.untracked.bool(False)
process.CondDB.connect = "sqlite_file:HeavyIonRPRcd_PbPb2018_offline.db"
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                       process.CondDB,
                                       toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRPRcd'),
                                                                  tag = cms.string('HeavyIonRPRcd_PbPb2018_offline')
                                                                  )
                                                         )
                                      )
process.es_prefer_flatparms = cms.ESPrefer('PoolDBESSource','')
process.evtplane_seq = cms.Sequence(process.hiEvtPlane * process.hiEvtPlaneFlat)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_HIMinimumBias_*', # MinimumBias  
]

# Add PbPb collision event selection
process.load('VertexCompositeAnalysis.VertexCompositeProducer.collisionEventSelection_cff')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.clusterCompatibilityFilter_cfi')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.hfCoincFilter_cff')
process.load("VertexCompositeAnalysis.VertexCompositeProducer.OfflinePrimaryVerticesRecovery_cfi")
process.colEvtSel = cms.Sequence(process.hfCoincFilter2Th4 * process.primaryVertexFilter * process.clusterCompatibilityFilter)

# Define the event selection sequence
process.eventFilter_HM = cms.Sequence(
#    process.hltFilter *
#    process.offlinePrimaryVerticesRecovery *
#    process.colEvtSel
)
process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

process.pcentandep_step = cms.Path(process.eventFilter_HM * process.cent_seq ) #* process.evtplane_seq)

# Define the analysis steps
process.load('MergingProducer.generalAndHiPixelTracks.MergingPixAndGenProducer_cfi')
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.corr_ana_PbPb2018.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracks")
process.corr_ana_PbPb2018.IsPPTrkQuality = cms.bool(False)
process.corr_ana_PbPb2018.IsHITrkQuality = cms.bool(False)
process.corr_ana_PbPb2018.IsCorr = cms.bool(False)
process.corr_ana_PbPb2018.IsDebug = cms.bool(True)
process.corr_ana_PbPb2018.centmin = cms.int32(0)
process.corr_ana_PbPb2018.centmax = cms.int32(200)
process.corr_ana_PbPb2018.etamultmin = cms.double(-1.0)
process.corr_ana_PbPb2018.etamultmax = cms.double(1.0)
process.corr_ana_PbPb2018.ptmultmin = cms.double(0.3)
process.corr_ana_PbPb2018.pttrgmin = cms.vdouble(0.3)
process.corr_ana_PbPb2018.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2018.etatrgmin = cms.double(-1.0)
process.corr_ana_PbPb2018.etatrgmax = cms.double(1.0)
process.corr_ana_PbPb2018.ptassmin = cms.vdouble(0.0)
process.corr_ana_PbPb2018.ptassmax = cms.vdouble(0.0)
process.corr_ana_PbPb2018.AssociateID = cms.string('CaloTower')
process.corr_ana_PbPb2018.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol2_v2.root')
process.corr_ana_PbPb2018.EffHistName = cms.string('Cor3D_fitsplit')

process.corr_ana_PbPb2018_cent05 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent510 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent1030 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent3050 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent50100 = process.corr_ana_PbPb2018.clone()
#process.corr_ana_PbPb2018_cent05.EffHistName = cms.string('Eff_0_5')
#process.corr_ana_PbPb2018_cent510.EffHistName = cms.string('Eff_0_5')
#process.corr_ana_PbPb2018_cent510.EffHistName = cms.string('Eff_5_10')
#process.corr_ana_PbPb2018_cent1030.EffHistName = cms.string('Eff_10_30')
#process.corr_ana_PbPb2018_cent3050.EffHistName = cms.string('Eff_30_50')
#process.corr_ana_PbPb2018_cent50100.EffHistName = cms.string('Eff_50_100')
process.corr_ana_PbPb2018_cent05.centmin = cms.int32(0)
process.corr_ana_PbPb2018_cent05.centmax = cms.int32(10)
process.corr_ana_PbPb2018_cent510.centmin = cms.int32(10)
process.corr_ana_PbPb2018_cent510.centmax = cms.int32(20)
process.corr_ana_PbPb2018_cent1030.centmin = cms.int32(20)
process.corr_ana_PbPb2018_cent1030.centmax = cms.int32(60)
process.corr_ana_PbPb2018_cent3050.centmin = cms.int32(60)
process.corr_ana_PbPb2018_cent3050.centmax = cms.int32(100)
process.corr_ana_PbPb2018_cent50100.centmin = cms.int32(100)
process.corr_ana_PbPb2018_cent50100.centmax = cms.int32(200)

process.generalAndHiPixelTracksTight = process.generalAndHiPixelTracks.clone(
  dxyErrMax = cms.double(2.0),
  dzErrMax = cms.double(2.0),
  ptErrMax = cms.double(0.05),
  chi2nMax = cms.double(0.15),
  dzErrMaxPixel = cms.double(15.0),
  dxyErrMaxPixel = cms.double(5.0)
)

process.generalAndHiPixelTracksLoose = process.generalAndHiPixelTracks.clone(
  dxyErrMax = cms.double(5.0),
  dzErrMax = cms.double(5.0),
  ptErrMax = cms.double(0.15),
  dzErrMaxPixel = cms.double(25.0),
  dxyErrMaxPixel = cms.double(9.0)
)

process.corr_ana_PbPb2018_tight = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_tight.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracksTight")
#process.corr_ana_PbPb2018_tight.EffFileName = cms.string('EffCorrectionsMergedPbPb2018_tight.root')
process.corr_ana_PbPb2018_tight.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol2_tight_v2.root')
process.corr_ana_PbPb2018_loose = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_loose.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracksLoose")
#process.corr_ana_PbPb2018_loose.EffFileName = cms.string('EffCorrectionsMergedPbPb2018_loose.root')
process.corr_ana_PbPb2018_loose.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol2_loose_v2.root')

process.corr_ana_PbPb2018_tight_cent05 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent510 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent1030 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent3050 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent5070 = process.corr_ana_PbPb2018_tight.clone()
#process.corr_ana_PbPb2018_tight_cent05.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_tight_cent510.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_tight_cent1030.EffHistName = cms.string('Cor_10_30')
#process.corr_ana_PbPb2018_tight_cent3050.EffHistName = cms.string('Cor_30_50')
#process.corr_ana_PbPb2018_tight_cent5070.EffHistName = cms.string('Cor_50_100')
process.corr_ana_PbPb2018_tight_cent05.centmin = cms.int32(0)
process.corr_ana_PbPb2018_tight_cent05.centmax = cms.int32(10)
process.corr_ana_PbPb2018_tight_cent510.centmin = cms.int32(10)
process.corr_ana_PbPb2018_tight_cent510.centmax = cms.int32(20)
process.corr_ana_PbPb2018_tight_cent1030.centmin = cms.int32(20)
process.corr_ana_PbPb2018_tight_cent1030.centmax = cms.int32(60)
process.corr_ana_PbPb2018_tight_cent3050.centmin = cms.int32(60)
process.corr_ana_PbPb2018_tight_cent3050.centmax = cms.int32(100)
process.corr_ana_PbPb2018_tight_cent5070.centmin = cms.int32(100)
process.corr_ana_PbPb2018_tight_cent5070.centmax = cms.int32(140)

process.corr_ana_PbPb2018_loose_cent05 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent510 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent1030 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent3050 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent5070 = process.corr_ana_PbPb2018_loose.clone()
#process.corr_ana_PbPb2018_loose_cent05.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_loose_cent510.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_loose_cent1030.EffHistName = cms.string('Cor_10_30')
#process.corr_ana_PbPb2018_loose_cent3050.EffHistName = cms.string('Cor_30_50')
#process.corr_ana_PbPb2018_loose_cent5070.EffHistName = cms.string('Cor_50_100')
process.corr_ana_PbPb2018_loose_cent05.centmin = cms.int32(0)
process.corr_ana_PbPb2018_loose_cent05.centmax = cms.int32(10)
process.corr_ana_PbPb2018_loose_cent510.centmin = cms.int32(10)
process.corr_ana_PbPb2018_loose_cent510.centmax = cms.int32(20)
process.corr_ana_PbPb2018_loose_cent1030.centmin = cms.int32(20)
process.corr_ana_PbPb2018_loose_cent1030.centmax = cms.int32(60)
process.corr_ana_PbPb2018_loose_cent3050.centmin = cms.int32(60)
process.corr_ana_PbPb2018_loose_cent3050.centmax = cms.int32(100)
process.corr_ana_PbPb2018_loose_cent5070.centmin = cms.int32(100)
process.corr_ana_PbPb2018_loose_cent5070.centmax = cms.int32(140)

process.corr_ana_PbPb2018_gen_cent05 = process.corr_ana_PbPb2018_cent05.clone()
process.corr_ana_PbPb2018_gen_cent05.EffFileName = cms.string('')
process.corr_ana_PbPb2018_gen_cent05.IsGenMult = cms.bool(True)
process.corr_ana_PbPb2018_gen_cent05.TriggerID = cms.string('GenParticle')
process.corr_ana_PbPb2018_gen_cent510 = process.corr_ana_PbPb2018_cent510.clone()
process.corr_ana_PbPb2018_gen_cent510.EffFileName = cms.string('')
process.corr_ana_PbPb2018_gen_cent510.IsGenMult = cms.bool(True)
process.corr_ana_PbPb2018_gen_cent510.TriggerID = cms.string('GenParticle')

process.corr_ana_PbPb2018_genmult_cent05 = process.corr_ana_PbPb2018_gen_cent05.clone()
process.corr_ana_PbPb2018_genmult_cent05.IsGenMult = cms.bool(True)
process.corr_ana_PbPb2018_genmult_cent05.IsGenCentrality = cms.bool(True)
process.corr_ana_PbPb2018_genmult_cent510 = process.corr_ana_PbPb2018_gen_cent510.clone()
process.corr_ana_PbPb2018_genmult_cent510.IsGenMult = cms.bool(True)
process.corr_ana_PbPb2018_genmult_cent510.IsGenCentrality = cms.bool(True)

process.corr_ana_PbPb2018_genmult = process.corr_ana_PbPb2018_genmult_cent05.clone()
process.corr_ana_PbPb2018_genmult.centmin = cms.int32(-1)
process.corr_ana_PbPb2018_genmult.centmax = cms.int32(-1)
process.corr_ana_PbPb2018_genmult.IsVtxSel = cms.bool(False)

process.corr_ana_PbPb2018_genmult_pt0 = process.corr_ana_PbPb2018_genmult.clone()
process.corr_ana_PbPb2018_genmult_pt0.ptmultmin = cms.double(0.)
process.corr_ana_PbPb2018_genmult_pt0.pttrgmin = cms.vdouble(0.)

process.ana_step = cms.Path(process.eventFilter_HM * process.generalAndHiPixelTracks * 
process.corr_ana_PbPb2018_cent05 *
process.corr_ana_PbPb2018_cent510 #*
#process.corr_ana_PbPb2018_cent1030 *
#process.corr_ana_PbPb2018_cent3050 *
#process.corr_ana_PbPb2018_cent50100 
#process.corr_ana_PbPb2018
)

process.ana_step_gen = cms.Path(process.eventFilter_HM * process.generalAndHiPixelTracks *
process.corr_ana_PbPb2018_gen_cent05 *
process.corr_ana_PbPb2018_gen_cent510 *
process.corr_ana_PbPb2018_genmult_cent05 *
process.corr_ana_PbPb2018_genmult_cent510 *
process.corr_ana_PbPb2018_genmult *
process.corr_ana_PbPb2018_genmult_pt0 
)

process.ana_step_syst = cms.Path(process.eventFilter_HM * process.generalAndHiPixelTracksTight * process.generalAndHiPixelTracksLoose *
  process.corr_ana_PbPb2018_tight_cent05 *
  process.corr_ana_PbPb2018_tight_cent510 *
#  process.corr_ana_PbPb2018_tight_cent1030 *
#  process.corr_ana_PbPb2018_tight_cent3050 *
#  process.corr_ana_PbPb2018_tight_cent5070 *
  process.corr_ana_PbPb2018_loose_cent05 *
  process.corr_ana_PbPb2018_loose_cent510 #*
#  process.corr_ana_PbPb2018_loose_cent1030 *
#  process.corr_ana_PbPb2018_loose_cent3050 *
#  process.corr_ana_PbPb2018_loose_cent5070
)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('dihadroncorrelation.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.pcentandep_step,
    process.ana_step,
    process.ana_step_syst,
    process.ana_step_gen
)

# Add recovery for offline primary vertex
#from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
#process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
#process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"
