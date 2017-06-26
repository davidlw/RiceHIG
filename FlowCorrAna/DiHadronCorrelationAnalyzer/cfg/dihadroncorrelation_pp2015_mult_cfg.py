import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015E5TeV_HM_v4/160101_051559/0000/pPb_HM_83.root'
'/store/user/davidlw/HighMultiplicity85/RecoSkim2015_2015BLowPU_ReTracking_v4/151106_150604/0000/pPb_HM_21.root'
#'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1018.root'
#'/store/user/davidlw/HighMultiplicity85/RecoSkim2015_2015CLowPU_ReTracking_v4/151106_104508/0000/pPb_HM_20.root'
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

process.ana = cms.Path(process.corr_ana)
process.corr_ana.IsCorr = cms.bool(False)
#process.corr_ana.IsDebug = cms.bool(True)
process.corr_ana.pttrgmin = cms.vdouble(0.0)
process.corr_ana.pttrgmax = cms.vdouble(10000.0)
#process.corr_ana.nmin = cms.int32(110)
#process.corr_ana.nmax = cms.int32(150)
process.corr_ana.EffFileName = cms.string('trkEff_pp_all_74X_origin.root')
