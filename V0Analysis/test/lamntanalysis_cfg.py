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
#'/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_ReTracking_v18/28b2b9cce04ec3f20baeb96fbd2295a8/pPb_HM_1618_2_sB4.root'
#'/store/user/davidlw/PAMinBiasUPC/PA2013_FlowCorr_PromptReco_MB_Gplus_ReTracking_v18/25c9a89be536a41c8ccb3c75e9fd9358/pPb_HM_1460_1_8tI.root'
'/store/user/davidlw/ReggeGribovPartonMCfix_EposLHC_5TeV_pPb/RecoSkim_ReTracking_v4_5M/5cde49c8740ff28f897f533d05a99dbc/pPb_MB_168_1_yGv.root'
                )
                            )

process.load("RiceHIG.V0Analysis.v0ntanalyzer_cff")
process.load("RiceHIG.V0Analysis.v0selector_cff")
process.load("RiceHIG.MyNtrkFilter.myntrkfilter_cff")

process.selectV0CandidatesNewlambda.v0CollName = cms.string("generalV0CandidatesLowPt")
process.v0ana_lambda.v0CollName = cms.InputTag("selectV0CandidatesNewlambda:Lambda")
process.v0ana_lambda.isFullInfo = cms.bool(False)


process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('lamntanalysis.root')
                                   )

process.v0analysis = cms.Sequence(process.selectV0CandidatesNewlambda*process.v0ana_lambda)

#process.p = cms.Path(process.ntrk185220_PA * process.v0analysis)
process.p = cms.Path(process.v0analysis)
