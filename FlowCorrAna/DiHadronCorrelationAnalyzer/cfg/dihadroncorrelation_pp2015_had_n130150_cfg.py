import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015E5TeV_HM_v4/160101_051559/0000/pPb_HM_83.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015E5TeV_HM_v4/160101_051559/0000/pPb_HM_82.root'
                )
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.ana = cms.Path(process.hltHM80105PP13TeV*process.corr_ana_pp)
process.corr_ana_pp.nmin = cms.int32(130)
process.corr_ana_pp.nmax = cms.int32(150)
