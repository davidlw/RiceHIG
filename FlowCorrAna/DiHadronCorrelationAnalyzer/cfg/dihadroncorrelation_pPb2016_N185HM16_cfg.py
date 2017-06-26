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
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/0809417D-2DAC-E611-BFD1-02163E01340B.root'
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/090/00000/18E99CF6-59AB-E611-8F92-02163E01440E.root',
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/090/00000/DC56AAB2-5EAB-E611-A27A-FA163E251515.root'
'/store/hidata/PARun2016C/PAHighMultiplicity7/AOD/PromptReco-v1/000/285/480/00000/5E0F96D9-08AF-E611-9C83-FA163E0C8993.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )

#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('FlowCorrAna.DiHadronCorrelationAnalyzer.evtselFilter_cff')

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM_pPb = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHM_pPb.HLTPaths = ['HLT_PAFullTracks_Multiplicity185*_v*']
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
process.corr_ana_N185210 = process.corr_ana.clone();
process.corr_ana_N185210.nmin = cms.int32(185)
process.corr_ana_N185210.nmax = cms.int32(210)
process.corr_ana_N210230 = process.corr_ana.clone();
process.corr_ana_N210230.nmin = cms.int32(210)
process.corr_ana_N210230.nmax = cms.int32(230)
process.corr_ana_N230250 = process.corr_ana.clone();
process.corr_ana_N230250.nmin = cms.int32(230)
process.corr_ana_N230250.nmax = cms.int32(250)

process.ana_N185210 = cms.Path(process.eventFilter_HM*process.corr_ana_N185210)
process.ana_N210230 = cms.Path(process.eventFilter_HM*process.corr_ana_N210230)
process.ana_N230250 = cms.Path(process.eventFilter_HM*process.corr_ana_N230250)
process.ana_N250270 = cms.Path(process.eventFilter_HM*process.corr_ana_N250270)
process.ana_N270300 = cms.Path(process.eventFilter_HM*process.corr_ana_N270300)
process.ana_N300330 = cms.Path(process.eventFilter_HM*process.corr_ana_N300330)
