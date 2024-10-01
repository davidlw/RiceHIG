import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
process = cms.Process('ANASKIM', Run3_pp_on_PbPb)

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
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it//store/hidata/HIRun2023A/HIForward0/MINIAOD/16Jan2024-v1/2810000/3151fd93-8b9b-40ea-9275-826a3977638c.root'),
#   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '132X_dataRun3_Prompt_v7', '')

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
process.hiCentrality.srcZDChits = cms.InputTag("QWzdcreco")
process.hiCentrality.srcReUse = cms.InputTag("hiCentrality","","reRECO")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("")
process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # photo-nuclear 
    'HLT_HIUPC_ZDC1nAsymXOR_MBHF*AND_PixelTrackMultiplicity*_v*'
]

# ZDC info
process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018Producer_cfi')
process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018RecHit_cfi')
#process.pcentandep_step = cms.Sequence( process.zdcdigi * process.QWzdcreco * process.cent_seq )
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
    process.primaryVertexFilterHI 
#    process.clusterCompatibilityFilter  *
#    process.phfCoincFilter2Th4 
#    process.pcentandep_step
)

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
#process.corr_ana_PbPb2023.centmin = cms.int32(0)
#process.corr_ana_PbPb2023.centmax = cms.int32(20)
process.corr_ana_PbPb2023.nmin = cms.int32(50)
process.corr_ana_PbPb2023.nmax = cms.int32(70)

# running on particle flow
process.corr_ana_PbPb2023.TriggerID = cms.string('PackedPFHadronHF')
#process.corr_ana_PbPb2023.AssociateID = cms.string('PackedPFHadron')
#process.corr_ana_PbPb2023.TriggerID = cms.string('Track')
process.corr_ana_PbPb2023.AssociateID = cms.string('Track')
#process.corr_ana_PbPb2023.etatrgmin = cms.double(-5.5)
#process.corr_ana_PbPb2023.etatrgmax = cms.double(5.5)
process.corr_ana_PbPb2023.etatrgmin = cms.double(-2.4)
process.corr_ana_PbPb2023.etatrgmax = cms.double(2.4)
process.corr_ana_PbPb2023.etaassmin = cms.double(-2.4)
process.corr_ana_PbPb2023.etaassmax = cms.double(2.4)
process.corr_ana_PbPb2023.pttrgmin = cms.vdouble(0.0)
process.corr_ana_PbPb2023.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2023.ptassmin = cms.vdouble(0.3)
process.corr_ana_PbPb2023.ptassmax = cms.vdouble(3.0)
process.corr_ana_PbPb2023.IsPtWeightTrg = cms.bool(True)
#process.corr_ana_PbPb2023.IsPtWeightAss = cms.bool(True)
process.corr_ana_PbPb2023.EffFileName = cms.string('')
process.corr_ana_PbPb2023.FakFileName = cms.string('')

process.ana_step = cms.Path(process.eventFilter_MB * process.corr_ana_PbPb2023)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('corr_pfcand_2023.root'))

# Define the process schedule

process.schedule = cms.Schedule(
    process.ana_step 
)

process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
process.eventFilter_MB.insert(0, process.unpackedTracksAndVertices)

from HLTrigger.Configuration.CustomConfigs import massReplaceInputTag
process = massReplaceInputTag(process,"offlinePrimaryVertices","unpackedTracksAndVertices")
process = massReplaceInputTag(process,"generalTracks","unpackedTracksAndVertices")
