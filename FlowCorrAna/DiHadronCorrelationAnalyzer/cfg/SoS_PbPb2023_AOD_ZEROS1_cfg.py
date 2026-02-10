import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
#process = cms.Process('ANASKIM', Run3_pp_on_PbPb)
process = cms.Process('ANASKIM')
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('PhysicsTools.PatAlgos.slimming.metFilterPaths_cff')
#process.load('Configuration.StandardSequences.PAT_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
#'root://xrootd-cms.infn.it//store/user/anstahll/CERN/PbPb2025/ZEROS/2025_11_09/HITrackerNZS/RECO_Step2_HITrackerNZS_HIRun2023A_v1_AODSIM_2025_11_09/251109_114314/0000/reco_step2_104.root',
#'root://xrootd-cms.infn.it//store/user/anstahll/CERN/PbPb2025/ZEROS/2025_11_09/HITrackerNZS/RECO_Step2_HITrackerNZS_HIRun2024AB_v1_AODSIM_2025_11_09/251109_204033/0000/reco_step2_101.root'
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_0.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_71.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_23.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_24.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_74.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_66.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_39.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_37.root',
#'file:/eos/cms/store/group/phys_heavyions/soohwan/TrackerStudies2025/reco_18.root',
'root://xrootd-cms.infn.it//store/group/phys_heavyions/wangj/RECO2025PbPb/aod_PhysicsHITrackerNZS4_399486_NZS_5per/reco_run399486_ls0016_streamPhysicsHITrackerNZS4_StorageManager.root'
)
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '150X_dataRun3_Prompt_v1', '')

# ==================================================================
# ==================== modification needed for 2023 data ===========
'''
from CondCore.CondDB.CondDB_cfi import *
process.es_pool = cms.ESSource("PoolDBESSource",
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
        cms.PSet(
            record = cms.string("HcalElectronicsMapRcd"),
            tag = cms.string("HcalElectronicsMap_2021_v2.0_data")
        )
    ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
        authenticationMethod = cms.untracked.uint32(1)
    )

process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')
process.es_ascii = cms.ESSource(
    'HcalTextCalibrations',
    input = cms.VPSet(
        cms.PSet(

            object = cms.string('ElectronicsMap'),
            file = cms.FileInPath("emap_2023_newZDC_v3.txt")

             )
        )
    )
'''
# =======================================================================

# Add PbPb centrality
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')
process.hiCentrality.produceHFhits = False
process.hiCentrality.produceHFtowers = False
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceZDChits = True
process.hiCentrality.produceETmidRapidity = False
process.hiCentrality.producePixelhits = False
process.hiCentrality.produceTracks = False
process.hiCentrality.producePixelTracks = False
process.hiCentrality.reUseCentrality = True
process.hiCentrality.srcZDChits = cms.InputTag("QWzdcreco")
process.hiCentrality.srcReUse = cms.InputTag("hiCentrality","","RECO")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("")
'''
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
       tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run3v1302x04_offline_Nominal"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])
'''    
#process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)
process.cent_seq = cms.Sequence(process.centralityBin)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_HIMinimumBiasHF1*', # MinimumBias  
#    'HLT_HIMinimumBiasHF1AND_*', # MinimumBias      
#    'HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v*',
#    'HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v*'
#     'HLT_HIUPC_ZDC1nAsymXOR_MBHF1AND_PixelTrackMultiplicity20_v*',
#     'HLT_HIUPC_ZDC1nXOR_MBHF1AND_PixelTrackMultiplicity20_v*',
]

process.hltFilterUCC = process.hltFilter.clone()
process.hltFilterUCC.HLTPaths = [
    'HLT_HIL1_UCC_0_0p5_v*', #UCC
    'HLT_HIL1_UCC_0_1_v*', #UCC
]

# ZDC info
#process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018Producer_cfi')
#process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018RecHit_cfi')
'''
process.load('HeavyIonsAnalysis.ZDCAnalysis.zdcanalyzer_cfi')
process.zdcanalyzer.doZDCRecHit = True
process.zdcanalyzer.doZDCDigi = True
process.zdcanalyzer.zdcRecHitSrc = cms.InputTag("QWzdcreco")
process.zdcanalyzer.zdcDigiSrc = cms.InputTag("hcalDigis", "ZDC")
process.zdcanalyzer.calZDCDigi = False
process.zdcanalyzer.verbose = False
process.zdcdigi.SOI = cms.untracked.int32(2)
'''
#process.pcentandep_step = cms.Sequence( process.zdcdigi * process.QWzdcreco * process.cent_seq )
#process.pcentandep_step = cms.Sequence( process.zdcdigi * process.QWzdcreco * process.zdcanalyzer * process.cent_seq )

# Add PbPb collision event selection
#process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
#process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.hffilter_cfi')
#process.primaryVertexFilterHI.src = cms.InputTag("offlinePrimaryVertices","HYBRID1")

process.eventFilter_MB = cms.Sequence(
    process.hltFilter *
    process.cent_seq
#    process.primaryVertexFilterHI * 
#    process.clusterCompatibilityFilter  *
#    process.phfCoincFilter2Th4 *
#    process.pcentandep_step
)
#process.eventFilter_MB_step = cms.Path( process.eventFilter_MB )

process.eventFilter_UCC = cms.Sequence(
    process.hltFilterUCC *
    process.cent_seq
#    process.primaryVertexFilterHI *
#    process.clusterCompatibilityFilter  *
#    process.phfCoincFilter2Th4 *
#    process.pcentandep_step
)
#process.eventFilter_UCC_step = cms.Path( process.eventFilter_UCC )

# Define the analysis steps
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.sosmeanptanalyzeraod_cfi")
process.sosmeanpt_ana.TrgTrackCollection = cms.InputTag("generalTracks","","ZEROS1")
process.sosmeanpt_ana.VertexCollection = cms.InputTag("offlinePrimaryVertices","","ZEROS1")
#process.sosmeanpt_ana.EffFileName = cms.string('GeneralTracks_Eff_3D_Nominal_MB.root')
#process.sosmeanpt_ana.EffHistName = cms.string('hEff_3D')
#process.sosmeanpt_ana.FakFileName = cms.string('GeneralTracks_Eff_3D_Nominal_MB.root')
#process.sosmeanpt_ana.FakHistName = cms.string('hFak_3D')

process.ana_step = cms.Path(process.eventFilter_MB *
  process.sosmeanpt_ana
)

# Configure the object that writes an output file
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("output.root")
)
#process.output_step = cms.EndPath(process.out)

# Define the output
#process.TFileService = cms.Service("TFileService", fileName = cms.string('SoS_2023_HYBRID1.root'))
#process.TFileService = cms.Service("TFileService", fileName = cms.string('SoS_2023_ZEROS1.root'))
process.TFileService = cms.Service("TFileService", fileName = cms.string('SoS_2025_ZEROS1.root'))

# Define the process schedule
process.schedule = cms.Schedule(
#    process.eventFilter_MB_step,
    process.ana_step
#    process.output_step
)
