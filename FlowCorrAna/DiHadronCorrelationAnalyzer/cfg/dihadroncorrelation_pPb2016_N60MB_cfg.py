import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/04214B66-30AC-E611-BFBC-FA163EBFF447.root',
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/06AF52AD-2EAC-E611-83B5-02163E014617.root',
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/0805B68E-2DAC-E611-BDE5-02163E014186.root',
'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/0809417D-2DAC-E611-BFD1-02163E01340B.root'
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/090/00000/18E99CF6-59AB-E611-8F92-02163E01440E.root',
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/090/00000/DC56AAB2-5EAB-E611-A27A-FA163E251515.root'
#'/store/hidata/PARun2016C/PAHighMultiplicity7/AOD/PromptReco-v1/000/285/480/00000/5E0F96D9-08AF-E611-9C83-FA163E0C8993.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )

#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('FlowCorrAna.DiHadronCorrelationAnalyzer.evtselFilter_cff')

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM_pPb = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHM_pPb.HLTPaths = ['HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_*_v*']
process.hltHM_pPb.andOr = cms.bool(True)
process.hltHM_pPb.throw = cms.bool(False)

process.eventFilter_HM = cms.Sequence(
    process.hltHM_pPb *
    process.PAcollisionEventSelection
)

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.ana = cms.Path(process.eventFilter_HM*process.corr_ana)
#process.corr_ana.IsCorr = cms.bool(False)
process.corr_ana.nmin = cms.int32(0)
process.corr_ana.nmax = cms.int32(10)

process.corr_ana_N010 = process.corr_ana.clone()
process.corr_ana_N010.nmin = cms.int32(0)
process.corr_ana_N010.nmax = cms.int32(10)
process.corr_ana_N1020 = process.corr_ana.clone()
process.corr_ana_N1020.nmin = cms.int32(10)
process.corr_ana_N1020.nmax = cms.int32(20)
process.corr_ana_N2030 = process.corr_ana.clone()
process.corr_ana_N2030.nmin = cms.int32(20)
process.corr_ana_N2030.nmax = cms.int32(30)
process.corr_ana_N3040 = process.corr_ana.clone()
process.corr_ana_N3040.nmin = cms.int32(30)
process.corr_ana_N3040.nmax = cms.int32(40)
process.corr_ana_N4050 = process.corr_ana.clone()
process.corr_ana_N4050.nmin = cms.int32(40)
process.corr_ana_N4050.nmax = cms.int32(50)
process.corr_ana_N5060 = process.corr_ana.clone()
process.corr_ana_N5060.nmin = cms.int32(50)
process.corr_ana_N5060.nmax = cms.int32(60)
process.corr_ana_N6070 = process.corr_ana.clone()
process.corr_ana_N6070.nmin = cms.int32(60)
process.corr_ana_N6070.nmax = cms.int32(70)
process.corr_ana_N7080 = process.corr_ana.clone()
process.corr_ana_N7080.nmin = cms.int32(70)
process.corr_ana_N7080.nmax = cms.int32(80)
process.corr_ana_N80100 = process.corr_ana.clone()
process.corr_ana_N80100.nmin = cms.int32(80)
process.corr_ana_N80100.nmax = cms.int32(100)
process.corr_ana_N100120 = process.corr_ana.clone()
process.corr_ana_N100120.nmin = cms.int32(100)
process.corr_ana_N100120.nmax = cms.int32(120)


process.ana_N6070 = cms.Path(process.eventFilter_HM*process.corr_ana_N6070)
process.ana_N7080 = cms.Path(process.eventFilter_HM*process.corr_ana_N7080)
process.ana_N80100 = cms.Path(process.eventFilter_HM*process.corr_ana_N80100)
process.ana_N100120 = cms.Path(process.eventFilter_HM*process.corr_ana_N100120)
