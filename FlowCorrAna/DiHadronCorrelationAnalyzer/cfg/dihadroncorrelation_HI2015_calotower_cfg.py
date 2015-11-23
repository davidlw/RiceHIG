import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/lixu/MinBias/Hydjet_0T_5020GeV_step3_1114/151114_135738/0000/hiReco0T_RAW2DIGI_L1Reco_RECO_10.root'
#'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110/8279ae7c7b9873cb2e7129d3c6d86a22/step3_RAW2DIGI_L1Reco_RECO_1005_1_PMw.root'
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

process.ana = cms.Path(process.corr_ana_HI)
process.corr_ana_HI.IsCorr = cms.bool(False)
process.corr_ana_HI.IsDebug = cms.bool(True)
process.corr_ana_HI.TriggerID = cms.string('CaloTower')
process.corr_ana_HI.etatrgmin = cms.double(-5.5)
process.corr_ana_HI.etatrgmax = cms.double(5.5)
process.corr_ana_HI.IsPtWeightTrg = cms.bool(True)
