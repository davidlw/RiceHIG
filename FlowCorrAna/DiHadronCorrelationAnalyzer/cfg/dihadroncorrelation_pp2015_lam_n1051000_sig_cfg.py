import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1018.root'
                )
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.load("RiceHIG.V0Analysis.v0selector_cff")
process.selectV0CandidatesNewlambda.v0CollName = cms.string("generalV0CandidatesLowPt")
#process.selectV0CandidatesNewlambda.vertexCollName = cms.InputTag('selectedVertex')
#process.selectV0CandidatesNewkshort.cosThetaCut = cms.double(0.99)
#process.selectV0CandidatesNewkshort.decayLSigCut = cms.double(2.5)

process.ana = cms.Path(process.selectV0CandidatesNewlambda*process.corr_ana_pp_la_sig)
#process.ana = cms.Path(process.hltHM110OnPP13TeV*process.selectV0CandidatesNewlambda*process.corr_ana)
#process.corr_ana.nvtxmax = cms.int32(1)
#process.corr_ana.V0CandidateCollection = cms.string('generalV0CandidatesLowPt')
process.corr_ana_pp_la_sig.V0CandidateCollection = cms.string('selectV0CandidatesNewlambda')
process.corr_ana_pp_la_sig.TriggerID = cms.string('Lambda')
process.corr_ana_pp_la_sig.nmin = cms.int32(105)
process.corr_ana_pp_la_sig.nmax = cms.int32(1000)
process.corr_ana_pp_la_sig.IsCheckTrgV0Dau = cms.bool(True)
