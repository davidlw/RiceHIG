import FWCore.ParameterSet.Config as cms

process = cms.Process("ANASKIM")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.MessageLogger.cerr.FwkReport.reportEvery = 200

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
'root://xrootd.unl.edu//store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00000/0008E152-62AE-E311-BB69-FA163E565820.root'
   ),
#   secondaryFileNames = cms.untracked.vstring('')
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'GR_P_V41::All'

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIFullTrack*_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.mb_step = cms.Path(process.hltHIMB)

process.load("RiceHIG.Skim2013.hianalysisSkimContent_cff")
process.output_mb = cms.OutputModule("PoolOutputModule",
   outputCommands = process.analysisSkimContent.outputCommands,
   fileName = cms.untracked.string('hiMB.root'),
   SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('mb_step')),
   dataset = cms.untracked.PSet(
     dataTier = cms.untracked.string('AOD'),
     filterName = cms.untracked.string('hiMB'))
)
process.output_mb_step = cms.EndPath(process.output_mb)

process.schedule = cms.Schedule(
   process.mb_step,
   process.output_mb_step
)
