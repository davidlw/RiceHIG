import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/HighMultiplicityEOF/RecoSkim2016_2016H_MD34_HM_v1/161011_171637/0000/pPb_HM_10.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.ana = cms.Path(process.hltHM105135PP13TeV*process.corr_ana)
process.corr_ana.IsCorr = cms.bool(False)
#process.corr_ana.pttrgmin = cms.vdouble(0.0)
#process.corr_ana.pttrgmax = cms.vdouble(10000.0)
