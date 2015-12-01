import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'root://xrootd-cms.infn.it//store/data/Run2015E/FullTrack/AOD/PromptReco-v1/000/262/273/00000/DC50F44C-EB96-E511-8351-02163E0142F1.root',
'root://xrootd-cms.infn.it//store/data/Run2015E/FullTrack/AOD/PromptReco-v1/000/262/273/00000/A8D81C53-EB96-E511-BA49-02163E014297.root'
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

#process.ana = cms.Path(process.hltHM85OnPP13TeV*process.corr_ana)
process.ana = cms.Path(process.corr_ana)
process.corr_ana.IsCorr = cms.bool(False)
#process.corr_ana.nvtxmax = cms.int32(1)
process.corr_ana.pttrgmin = cms.vdouble(0.0)
process.corr_ana.pttrgmax = cms.vdouble(10000)
