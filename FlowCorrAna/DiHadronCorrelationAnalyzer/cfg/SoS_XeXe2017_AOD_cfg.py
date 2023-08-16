import FWCore.ParameterSet.Config as cms
process = cms.Process('ANASKIM')
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
#   fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/hidata/XeXeRun2017/HIMinimumBias1/MINIAOD/PromptReco-v1/000/304/906/00000/DA4F2BDC-BAB1-E711-9F81-02163E01A4CE.root'),
   fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/hidata/XeXeRun2017/HIMinimumBias1/AOD/13Dec2017-v1/60000/028E25B7-33E9-E711-B098-3C4A92F8FC10.root')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v2', '')
#process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
   cms.PSet(record = cms.string("HeavyIonRcd"),
      tag = cms.string("CentralityTable_HFtowers200_DataXeXe_eff95_run2v941x02_offline"),
      connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
      label = cms.untracked.string("HFtowersEPOSLHC")
   ),
])

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
process.hiCentrality.srcReUse = cms.InputTag("hiCentrality","","RECO")
process.hiCentrality.srcTracks = cms.InputTag("generalTracks")
process.hiCentrality.srcVertex = cms.InputTag("offlinePrimaryVertices")

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("EPOSLHC")
process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_part*', # MinimumBias  
]

## event selection
#primaryVertexFilter
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True), # otherwise it won't filter the events
)

#BeamScrapingFilter
process.NoScraping = cms.EDFilter("FilterOutScraping",
 applyfilter = cms.untracked.bool(True),
 debugOn = cms.untracked.bool(False),
 numtrack = cms.untracked.uint32(10),
 thresh = cms.untracked.double(0.25)
)

#phfCoincFilter3
process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")
process.hfPosFilter3 = process.hfPosFilter.clone(minNumber=cms.uint32(3))
process.hfNegFilter3 = process.hfNegFilter.clone(minNumber=cms.uint32(3))
process.hfCoincFilter3 = cms.Sequence(
    process.towersAboveThreshold
    + process.hfPosTowers
    + process.hfNegTowers
    + process.hfPosFilter3
    + process.hfNegFilter3
)
#all the event selections
process.eventFilter_HM = cms.Sequence(
        process.primaryVertexFilter
        + process.NoScraping
        + process.hfCoincFilter3
)
process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )
process.pcent_step = cms.Path( process.eventFilter_HM * process.cent_seq )

# Define the analysis steps
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.corr_ana_XeXe2017 = process.corr_ana_PbPb2018.clone()
process.corr_ana_XeXe2017.TrgTrackCollection = cms.InputTag("generalTracks")
process.corr_ana_XeXe2017.VertexCollection = cms.InputTag("offlinePrimaryVertices")
process.corr_ana_XeXe2017.IsPPTrkQuality = cms.bool(True)
process.corr_ana_XeXe2017.IsHITrkQuality = cms.bool(False)
process.corr_ana_XeXe2017.IsCorr = cms.bool(False)
process.corr_ana_XeXe2017.IsDebug = cms.bool(True)
process.corr_ana_XeXe2017.centmin = cms.int32(0)
process.corr_ana_XeXe2017.centmax = cms.int32(200)
process.corr_ana_XeXe2017.etamultmin = cms.double(-1.0)
process.corr_ana_XeXe2017.etamultmax = cms.double(1.0)
process.corr_ana_XeXe2017.ptmultmin = cms.double(0.3)
process.corr_ana_XeXe2017.pttrgmin = cms.vdouble(0.3)
process.corr_ana_XeXe2017.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_XeXe2017.etatrgmin = cms.double(-1.0)
process.corr_ana_XeXe2017.etatrgmax = cms.double(1.0)
process.corr_ana_XeXe2017.ptassmin = cms.vdouble(0.0)
process.corr_ana_XeXe2017.ptassmax = cms.vdouble(0.0)
process.corr_ana_XeXe2017.AssociateID = cms.string('Track')
process.corr_ana_XeXe2017.EffFileName = cms.string('XeXe_eff_table_94x_cent.root')
process.corr_ana_XeXe2017.EffHistName = cms.string('rTotalEff3D_0_10')

process.corr_ana_XeXe2017_cent05 = process.corr_ana_XeXe2017.clone()
process.corr_ana_XeXe2017_cent510 = process.corr_ana_XeXe2017.clone()
process.corr_ana_XeXe2017_cent1030 = process.corr_ana_XeXe2017.clone()
process.corr_ana_XeXe2017_cent3050 = process.corr_ana_XeXe2017.clone()
process.corr_ana_XeXe2017_cent50100 = process.corr_ana_XeXe2017.clone()

#process.corr_ana_XeXe2017_cent1030.EffHistName = cms.string('rTotalEff3D_10_30')
#process.corr_ana_XeXe2017_cent3050.EffHistName = cms.string('rTotalEff3D_30_50')
#process.corr_ana_XeXe2017_cent50100.EffHistName = cms.string('rTotalEff3D_50_100')
process.corr_ana_XeXe2017_cent05.centmin = cms.int32(0)
process.corr_ana_XeXe2017_cent05.centmax = cms.int32(10)
process.corr_ana_XeXe2017_cent510.centmin = cms.int32(10)
process.corr_ana_XeXe2017_cent510.centmax = cms.int32(20)
process.corr_ana_XeXe2017_cent1030.centmin = cms.int32(20)
process.corr_ana_XeXe2017_cent1030.centmax = cms.int32(60)
process.corr_ana_XeXe2017_cent3050.centmin = cms.int32(60)
process.corr_ana_XeXe2017_cent3050.centmax = cms.int32(100)
process.corr_ana_XeXe2017_cent50100.centmin = cms.int32(100)
process.corr_ana_XeXe2017_cent50100.centmax = cms.int32(200)

process.ana_step = cms.Path(process.eventFilter_HM *
  process.corr_ana_XeXe2017_cent05 *
  process.corr_ana_XeXe2017_cent510 *
  process.corr_ana_XeXe2017_cent1030 *
  process.corr_ana_XeXe2017_cent3050 *
  process.corr_ana_XeXe2017_cent50100
)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('dihadroncorrelation.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.pcent_step,
    process.ana_step
)


#process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
#process.eventFilter_HM.insert(0, process.unpackedTracksAndVertices)
#from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
#process = MassReplaceInputTag(process,"offlinePrimaryVertices","unpackedTracksAndVertices")
#process = MassReplaceInputTag(process,"generalTracks","unpackedTracksAndVertices")
