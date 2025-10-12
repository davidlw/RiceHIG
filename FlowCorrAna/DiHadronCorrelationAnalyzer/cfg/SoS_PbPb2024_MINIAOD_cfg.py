import FWCore.ParameterSet.Config as cms

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
           'root://xrootd-cms.infn.it//store/hidata/HIRun2024B/HIPhysicsRawPrime0/MINIAOD/PromptReco-v2/000/388/468/00000/533da203-94b3-4f7c-9f98-14a5b8046aa6.root'
)
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2024_HI_387853_388784_Golden.json').getVLuminosityBlockRange()

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '141X_dataRun3_Prompt_v3', '')

# ==================================================================
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
process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_HIMinimumBiasHF1ANDZDC1nOR_*', # MinimumBias  
]

process.hltFilterUCC = process.hltFilter.clone()
process.hltFilterUCC.HLTPaths = [
    'HLT_HIL1_UCC_0_0p5_v*', #UCC
    'HLT_HIL1_UCC_0_1_v*', #UCC
]

# ZDC info
process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018Producer_cfi')
process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018RecHit_cfi')
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
process.pcentandep_step = cms.Sequence( process.zdcdigi * process.QWzdcreco * process.cent_seq )
#process.pcentandep_step = cms.Sequence( process.zdcdigi * process.QWzdcreco * process.zdcanalyzer * process.cent_seq )

# Add PbPb collision event selection
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hffilter_cfi')
process.primaryVertexFilterHI.src = cms.InputTag("offlinePrimaryVertices")

process.eventFilter_MB = cms.Sequence(
    process.hltFilter *
    process.primaryVertexFilterHI * 
    process.clusterCompatibilityFilter  *
    process.phfCoincFilter2Th4 *
    process.pcentandep_step
)
#process.eventFilter_MB_step = cms.Path( process.eventFilter_MB )

process.eventFilter_UCC = cms.Sequence(
    process.hltFilterUCC *
    process.primaryVertexFilterHI *
    process.clusterCompatibilityFilter  *
    process.phfCoincFilter2Th4 *
    process.pcentandep_step
)
#process.eventFilter_UCC_step = cms.Path( process.eventFilter_UCC )

# Define the analysis steps
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.sosmeanptanalyzer_cfi")
process.sosmeanpt_ana.TrgTrackCollection = cms.InputTag("generalTracks")
process.sosmeanpt_ana.VertexCollection = cms.InputTag("offlinePrimaryVertices")
process.sosmeanpt_ana.IsHITrkQuality = cms.bool(True)
process.sosmeanpt_ana.IsPPTrkQuality = cms.bool(False)
process.sosmeanpt_ana.EffFileName = cms.string('')
#process.sosmeanpt_ana.EffFileName = cms.string('EffCorrectionsPbPb2023_general_3D_cheb4_mcnpix_miniAOD_v6btight.root')
#process.sosmeanpt_ana.EffHistName = cms.string('Cor3D')
#process.sosmeanpt_ana.FakFileName = cms.string('GeneralTracks_Eff_3D_Nominal_MB.root')
#process.sosmeanpt_ana.FakHistName = cms.string('hFak_3D')

process.sosmeanpt_ana_ucc = process.sosmeanpt_ana.clone()

process.ana_step = cms.Path(process.eventFilter_MB *
  process.sosmeanpt_ana
)

process.ana_ucc_step = cms.Path(process.eventFilter_UCC *
  process.sosmeanpt_ana_ucc
)

# Configure the object that writes an output file
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("output.root")
)
#process.output_step = cms.EndPath(process.out)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('SoS_2024.root'))

# Define the process schedule
process.schedule = cms.Schedule(
#    process.eventFilter_MB_step,
    process.ana_step
#    process.ana_ucc_step,
#    process.output_step
)

process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
process.eventFilter_MB.insert(0, process.unpackedTracksAndVertices)
process.eventFilter_UCC.insert(0, process.unpackedTracksAndVertices)

from HLTrigger.Configuration.CustomConfigs import massReplaceInputTag
process = massReplaceInputTag(process,"offlinePrimaryVertices","unpackedTracksAndVertices")
process = massReplaceInputTag(process,"generalTracks","unpackedTracksAndVertices")

# Add recovery for offline primary vertex
#from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
#process = massReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
#process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"
