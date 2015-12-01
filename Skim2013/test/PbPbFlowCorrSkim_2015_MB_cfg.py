import FWCore.ParameterSet.Config as cms
process = cms.Process("ANASKIM")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

#process.source = cms.Source("PoolSource",
#   fileNames = cms.untracked.vstring(
#'file:/mnt/hadoop/cms/store/user/davidlw/HIMinBias2015/recoExpress_15.root'
#)
#)

import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('fileWithInfoYouWant.txt') 
#mylist.extend ( FileUtils.loadListFromFile ('moreInfoIwant.txt') )
readFiles = cms.untracked.vstring( *mylist)

process.source = cms.Source('PoolSource', fileNames = readFiles)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#process.GlobalTag.globaltag = 'GR_P_V41::All'

# =============== Import Sequences =====================

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMB.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1']
process.hltMB.andOr = cms.bool(True)
process.hltMB.throw = cms.bool(False)

process.eventFilter_MB = cms.Sequence( 
    process.hltMB
)
process.eventFilter_MB_step = cms.Path( process.eventFilter_MB )

process.load("RiceHIG.Skim2013.hianalysisSkimContent_cff")
process.output_MB = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('/net/hisrv0001/home/davidlw/scratch1/PbPb_MB.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_MB_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD'),
      filterName = cms.untracked.string('PbPb_MB'))
)
process.output_MB_step = cms.EndPath(process.output_MB)

process.schedule = cms.Schedule(
    process.eventFilter_MB_step,
    process.output_MB_step
)
