import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
process = cms.Process('ANASKIM2',eras.Run2_2018_pp_on_AA)

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('file:/eos/cms/store/group/phys_heavyions/flowcorr/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/TestSample_QCD_Pt_15to30_TuneCP5_13TeV_pythia8_miniaod/210222_154136/0000/AOD_1.root'),
#   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))

# Set the global tag
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '') 

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_*', # MinimumBias  
]

# Add PbPb collision event selection
process.load('VertexCompositeAnalysis.VertexCompositeProducer.collisionEventSelection_cff')
process.colEvtSel = cms.Sequence(process.primaryVertexFilter)

# Define the event selection sequence
process.eventFilter = cms.Sequence(
    process.hltFilter *
    process.colEvtSel
)
process.eventFilter_step = cms.Path( process.eventFilter )

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epptdecomatrix_cff")

process.ana_step = cms.Path(process.eventFilter 
                          * process.epptdecomatrix_ana_pp
)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('epptdecomatrix.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.eventFilter_step,
    process.ana_step 
)

from FlowCorrAna.DiHadronCorrelationAnalyzer.PATAlgos_cff import changeToMiniAOD
changeToMiniAOD(process)
