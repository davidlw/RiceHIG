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

process.corr_ana_pPb.etacms = cms.double(-0.465)
process.corr_ana_pPb_FF = process.corr_ana_pPb.clone()
process.corr_ana_pPb_FF.etatrgmin = cms.double(-1.935)
process.corr_ana_pPb_FF.etatrgmax = cms.double(-1.535)
process.corr_ana_pPb_FF.etaassmin = cms.double(-1.935)
process.corr_ana_pPb_FF.etaassmax = cms.double(-1.535)

process.corr_ana_pPb_FC = process.corr_ana_pPb.clone()
process.corr_ana_pPb_FC.etatrgmin = cms.double(-1.935)
process.corr_ana_pPb_FC.etatrgmax = cms.double(-1.535)
process.corr_ana_pPb_FC.etaassmin = cms.double(-0.2)
process.corr_ana_pPb_FC.etaassmax = cms.double(0.2)

process.corr_ana_pPb_FB = process.corr_ana_pPb.clone()
process.corr_ana_pPb_FB.etatrgmin = cms.double(-1.935)
process.corr_ana_pPb_FB.etatrgmax = cms.double(-1.535)
process.corr_ana_pPb_FB.etaassmin = cms.double(1.535)
process.corr_ana_pPb_FB.etaassmax = cms.double(1.935)

process.ana_ff = cms.Path(process.eventFilter_HM*process.corr_ana_pPb_FF)
process.ana_fc = cms.Path(process.eventFilter_HM*process.corr_ana_pPb_FC)
process.ana_fb = cms.Path(process.eventFilter_HM*process.corr_ana_pPb_FB)


