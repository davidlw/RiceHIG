import FWCore.ParameterSet.Config as cms

process = cms.Process("V0Ana")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### standard includes
#process.load("Configuration.EventContent.EventContent_cff")

### conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'STARTHI53_V17::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
                        'file:/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/RiceHIG/Skim2013/test/pPb_HM.root'
                ),
                secondaryFileNames=cms.untracked.vstring(
                        '/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_ReTracking_v18/28b2b9cce04ec3f20baeb96fbd2295a8/pPb_HM_1618_2_sB4.root',
                )  
                            )

process.load("RiceHIG.V0Analysis.xintanalyzer_cff")
process.load("RiceHIG.MyNtrkFilter.myntrkfilter_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('xintanalysis.root')
                                   )

process.xianalysis = cms.Sequence(process.xiana)

process.p = cms.Path(process.ntrk185220_PA * process.xianalysis)

#process.schedule = cms.Schedule(process.p)
