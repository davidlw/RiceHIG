import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step2_20151106/0e34df14ec22ccb8b9e974a58aa5d325/step2_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_1003_1_qan.root'
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
process.corr_ana.pttrgmin = cms.vdouble(0.0)
process.corr_ana.pttrgmax = cms.vdouble(10000.0)
process.corr_ana.TriggerID = cms.string('GenParticle')
process.corr_ana.AssociateID = cms.string('GenParticle')
process.corr_ana.IsGenMult = cms.bool(True)
process.corr_ana.IsVtxSel = cms.bool(False)
