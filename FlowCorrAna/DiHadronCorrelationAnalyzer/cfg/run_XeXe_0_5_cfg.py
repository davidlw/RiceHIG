import FWCore.ParameterSet.Config as cms

process = cms.Process('TRACKANA')
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")
process.load('2pc.BigFlow.BigFlowAnalyzer_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('corr.root')
)


# Input source
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames =  cms.untracked.vstring(
#'root://cmsxrootd.fnal.gov//store/hidata/XeXeRun2017/HIMinimumBias1/AOD/PromptReco-v1/000/304/906/00000/CEF3F710-BDB1-E711-9652-02163E019BB5.root'
'/store/hidata/XeXeRun2017/HIMinimumBias1/AOD/13Dec2017-v1/60000/028E25B7-33E9-E711-B098-3C4A92F8FC10.root'
#'/store/hidata/XeXeRun2017/HIMinimumBias/AOD/PromptReco-v1/000/304/830/00000/EEC82EE5-BDB0-E711-9FDA-02163E01A337.root'
#'/store/hidata/XeXeRun2017/HIMinimumBias11/AOD/PromptReco-v1/000/304/880/00000/8ED1630E-0CB1-E711-9E49-02163E01469E.root'
#'/store/hidata/XeXeRun2017/HIMinimumBias/AOD/PromptReco-v1/000/304/848/00000/8E05492F-C8B0-E711-BD30-02163E01430D.root'
#'/store/hidata/XeXeRun2017/HIMinimumBias/AOD/PromptReco-v1/000/304/870/00000/8A076E80-EAB0-E711-9685-02163E014252.root'
#'/store/hidata/XeXeRun2017/HIMinimumBias11/AOD/PromptReco-v1/000/304/866/00000/E8BECA01-DEB0-E711-BABE-02163E019E8F.root'
#'/store/data/Run2015E/FullTrack/AOD/PromptReco-v1/000/262/157/00000/1618B672-9E91-E511-BA4A-02163E01386D.root'
#'file:/afs/cern.ch/work/q/qwang/public/PbPb2015_tracking/pixeltracking_1.root'
),

#    eventsToProcess = cms.untracked.VEventRange('1:6652:352538')

)
### centrality ###

#process.HeavyIonGlobalParameters = cms.PSet(
#    centralitySrc = cms.InputTag("hiCentrality"),
#    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
#)



### Track cuts ###
# input collections
process.BigFlow.centralitySrc = cms.InputTag("centralityBin","HFtowers")
process.BigFlow.trackSrc = cms.InputTag("generalTracks")
#process.BigFlow.trackSrc1 = cms.InputTag("hiGeneralAndPixelTracks")
process.BigFlow.qualityString = cms.string("highPurity")
process.BigFlow.pfCandSrc = cms.untracked.InputTag("particleFlowTmp")
process.BigFlow.jetSrc = cms.InputTag("akPu4CaloJets")
# options
process.BigFlow.useCentrality = True 
process.BigFlow.applyTrackCuts = True
process.BigFlow.fillNTuples = False
process.BigFlow.applyVertexZCut = True
process.BigFlow.doVtxReweighting = False
process.BigFlow.doCaloMatched = False
# cut values
process.BigFlow.dxyErrMax = 3.0
process.BigFlow.dzErrMax = 3.0
process.BigFlow.ptErrMax = 0.1
#process.BigFlow.effTable = "/afs/cern.ch/work/m/mstojano/private/CENT_TEST/XeXe/CMSSW_9_2_12_patch1/src/2pc/BigFlow/test/XeXe_eff_table_92x.root"
process.BigFlow.effTable = "XeXe_eff_table_94x_cent.root"
#process.HITrackCorrections.crossSection = 1.0 #1.0 is no reweigh
#events of interest
process.BigFlow.centmax = 5 
process.BigFlow.centmin = 0
#Analysis parameters
process.BigFlow.pt_trigmax = cms.vdouble(3.)
process.BigFlow.pt_trigmin = cms.vdouble(.3)
process.BigFlow.pt_assmax = cms.vdouble(.4,.5,.6,.8,1.,1.25,1.50,2.0,2.5,3.0,3.5,4.0,5.,6.,7.,8.,10.)
process.BigFlow.pt_assmin = cms.vdouble(.3,.4,.5,.6,.8,1.00,1.25,1.5,2.0,2.5,3.0,3.5,4.,5.,6.,7.,8.0)
process.BigFlow.pt_tbins = 1
process.BigFlow.pt_nbins = 17

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
process.eventSelections = cms.Sequence(
        process.primaryVertexFilter
        + process.NoScraping
        + process.hfCoincFilter3
)

# trigger selection
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltHIL1MinimumBiasHF_OR_SinglePixelTrack = process.hltHighLevel.clone()
process.hltHIL1MinimumBiasHF_OR_SinglePixelTrack.HLTPaths = ["HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_part*"]
process.hltHIL1MinimumBiasHF_OR_SinglePixelTrack.andOr = cms.bool(True)
process.hltHIL1MinimumBiasHF_OR_SinglePixelTrack.throw = cms.bool(False)

###

#GlobalTak
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
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

#Centrality

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



###
process.p = cms.Path(
		      process.hltHIL1MinimumBiasHF_OR_SinglePixelTrack *
		      process.eventSelections *
		      process.hiCentrality *
		      process.centralityBin *
                      process.BigFlow
)
