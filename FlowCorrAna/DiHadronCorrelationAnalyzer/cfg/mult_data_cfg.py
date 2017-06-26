import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/ppRECO_run263233/part1000_std_v1/160113_231604/0000/step2pp_RAW2DIGI_L1Reco_AOD_46.root'
#'/store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v2/160215_223734/0000/step2pp_RAW2DIGI_L1Reco_RECO_268.root'
'file:/export/d00/scratch/davidlw/OSG_CMSSW/CMSSW_7_5_8_patch2/src/step2pp_RAW2DIGI_L1Reco_RECO.root'
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
