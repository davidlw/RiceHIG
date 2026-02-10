import FWCore.ParameterSet.Config as cms

process = cms.Process('ANASKIM')
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
           'root://cmsxrootd.fnal.gov//store/hidata/NeNeRun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/272/00000/21b15b8b-2cbb-47dc-aeb6-d122a90e86df.root'
   )
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2025Nene_394269_394272_golden.json').getVLuminosityBlockRange()

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Other statements
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = cms.string('150X_dataRun3_Prompt_v1')

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_MinimumBiasHF_OR_BptxAND_v*'
#    'HLT_OxyZeroBias_v*'
]

# Add PbPb collision event selection
process.load('VertexCompositeAnalysis.VertexCompositeProducer.collisionEventSelection_cff')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.primaryVertexRecoveryForUPC_cfi')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.hffilterPF_cfi')

process.primaryVertexFilterHI = process.primaryVertexFilter.clone(src = "offlinePrimaryVertices")

process.load('HeavyIonsAnalysis.VertexAnalysis.pileupvertexfilter_cfi')
process.pileupvertexfilter.doOO = False
process.pileupvertexfilter.doNeNe = True

process.eventFilter_MB = cms.Sequence(
    process.hltFilter *
    process.primaryVertexFilterHI *
    process.pileupvertexfilter *
    process.phfCoincFilterPF2Th4
)
process.eventFilter_MB_step = cms.Path( process.eventFilter_MB )

# Define the analysis steps
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.sosmeanptanalyzer_cfi")
process.sosmeanpt_ana.TrgTrackCollection = cms.InputTag("generalTracks")
process.sosmeanpt_ana.VertexCollection = cms.InputTag("offlinePrimaryVertices")
process.sosmeanpt_ana.IsHITrkQuality = cms.bool(True)
process.sosmeanpt_ana.IsPPTrkQuality = cms.bool(False)
process.sosmeanpt_ana.EffFileName = cms.string('EffFakVsNpixel3D_OO2025.root')
process.sosmeanpt_ana.FakFileName = cms.string('')
process.sosmeanpt_ana.EffHistName = cms.string('hCombFit3D')
process.sosmeanpt_ana.FakHistName = cms.string('')

process.ana_step = cms.Path(process.eventFilter_MB *
  process.sosmeanpt_ana
)

# Configure the object that writes an output file
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("output.root")
)
#process.output_step = cms.EndPath(process.out)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('SoS_NeNe2025.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.eventFilter_MB_step,
    process.ana_step
#    process.output_step
)

process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
process.eventFilter_MB.insert(0, process.unpackedTracksAndVertices)

from HLTrigger.Configuration.CustomConfigs import massReplaceInputTag
process = massReplaceInputTag(process,"offlinePrimaryVertices","unpackedTracksAndVertices")
process = massReplaceInputTag(process,"generalTracks","unpackedTracksAndVertices")
