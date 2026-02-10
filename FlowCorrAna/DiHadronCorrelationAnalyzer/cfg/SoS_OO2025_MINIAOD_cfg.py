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
           'root://cmsxrootd.fnal.gov//store/hidata/OORun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/209/00000/07650c6a-82e9-42c5-a613-51f9ae2165d5.root'
#    'root://cmsxrootd.fnal.gov///store/user/anstahll/CERN/OXY2025/RERECO/2025_07_15/IonPhysics/crab_Run394153_OORun2025-PromptReco-v1_Run3_2025_OXY_2025_07_15/250722_192942/0000/reco_1.root'
   )
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2025OO_394153_394217_golden.json').getVLuminosityBlockRange()

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
process.pileupvertexfilter.doOO = True
process.pileupvertexfilter.doNeNe = False
# OO 1sigma
#process.pileupvertexfilter.surfaceCutParameters1OO = cms.vdouble(0.815982, 0.723081, 0.661896, 0.611045, 0.57925, 0.545224, 0.460456, 0.330665, 0.368534, 0.0500001)
#process.pileupvertexfilter.surfaceCutParameters2OO = cms.vdouble(5.90939, 2.59066, 2.04513, 1.95563, 1.92411, 1.53559, 1.79173, 2.20266, 1.97243, 2.03752)
# OO 3sigma
#process.pileupvertexfilter.surfaceCutParameters1OO = cms.vdouble(0.878362, 0.78132, 0.72238, 0.67322, 0.640962, 0.624485, 0.53948, 0.410699, 0.459283, 0.0500008)
#process.pileupvertexfilter.surfaceCutParameters2OO = cms.vdouble(12.6986, 5.29356, 3.89238, 3.42843, 3.32093, 1.98595, 2.22217, 2.70285, 2.15944, 2.14269)
# OO 2sigma, ANGANTYR
#process.pileupvertexfilter.surfaceCutParameters1OO = cms.vdouble(0.866138, 0.741273, 0.666387, 0.619754, 0.588603, 0.549282, 0.46138, 0.256335, 0.05, 0.0500001)
#process.pileupvertexfilter.surfaceCutParameters2OO = cms.vdouble(25.6879, 4.66889, 3.35005, 2.75572, 2.498, 2.08069, 2.2148, 2.64765, 1.86201, 1.71259)

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
process.TFileService = cms.Service("TFileService", fileName = cms.string('SoS_OO2025.root'))

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
