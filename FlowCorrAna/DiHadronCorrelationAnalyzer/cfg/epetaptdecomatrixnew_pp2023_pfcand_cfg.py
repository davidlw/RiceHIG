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
              'root://xrootd-cms.infn.it//store/data/Run2023F/PPRefZeroBias0/MINIAOD/PromptReco-v1/000/373/710/00000/d6eee50b-9ff4-469f-b217-d4a336dcbfbc.root'),
#   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2023_ppref_373710_Muon.json').getVLuminosityBlockRange()

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '132X_dataRun3_Prompt_v7', '')

# ==================== modification needed for 2023 pp data ===========

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # ZeroBias
     'HLT_PPRefZeroBias_v*', # ZeroBias 
]

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
)

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epetaptdecomatrixnew_cff")
# running on particle flow
process.epetaptdecomatrixnew_ana_pp2023.TriggerID = cms.string('Track')
process.epetaptdecomatrixnew_ana_pp2023.AssociateID = cms.string('Track')
process.epetaptdecomatrixnew_ana_pp2023.etatrgmin = cms.double(-5.4)
process.epetaptdecomatrixnew_ana_pp2023.etatrgmax = cms.double(5.4)
process.epetaptdecomatrixnew_ana_pp2023.etaassmin = cms.double(-5.4)
process.epetaptdecomatrixnew_ana_pp2023.etaassmax = cms.double(5.4)
process.epetaptdecomatrixnew_ana_pp2023.pttrgmin = cms.vdouble(0.3)
process.epetaptdecomatrixnew_ana_pp2023.pttrgmax = cms.vdouble(3.0)
process.epetaptdecomatrixnew_ana_pp2023.ptassmin = cms.vdouble(0.0)
process.epetaptdecomatrixnew_ana_pp2023.ptassmax = cms.vdouble(0.0)
process.epetaptdecomatrixnew_ana_pp2023.IsPtWeightTrg = cms.bool(True)
process.epetaptdecomatrixnew_ana_pp2023.IsPtWeightAss = cms.bool(True)
#process.epetaptdecomatrixnew_ana_pp2023.EffFileName = cms.string('.root')
#process.epetaptdecomatrixnew_ana_pp2023.FakFileName = cms.string('.root')
#process.epetaptdecomatrixnew_ana_pp2023.EffHistName = cms.string('hEff_3D')
#process.epetaptdecomatrixnew_ana_pp2023.FakHistName = cms.string('hFak_3D')

process.ana_step = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_pp2023)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('epetaptdecomatrixnew_pp_pfcand.root'))

# Define the process schedule

process.schedule = cms.Schedule(
    process.ana_step
)

process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
process.eventFilter_MB.insert(0, process.unpackedTracksAndVertices)

from HLTrigger.Configuration.CustomConfigs import massReplaceInputTag
process = massReplaceInputTag(process,"offlinePrimaryVertices","unpackedTracksAndVertices")
process = massReplaceInputTag(process,"generalTracks","unpackedTracksAndVertices")
