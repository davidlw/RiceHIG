import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/HIMinBiasUPC/PR2011_MBUCC_TRKANASKIM_official_v1/71a7d203fff2b3f389673e6fdd587ee0/hiGoodColl_1023_1_S52.root'
#'root://xrootd.unl.edu//store/user/appeltel/HIMinBiasUPC/pixelTrackReco_devel_v0/a236e4501225ae15b3601563d612abb5/pixeltrackreco_6_1_qSR.root'
'file:/mnt/hadoop/cms/store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_2654_1_Kdg.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('lampol.root')
                                   )

process.load("RiceHIG.V0Analysis.v0selector_cff")
process.selectV0CandidatesNewlambda.v0CollName = cms.string("generalV0CandidatesLowPt")

process.ana = cms.Path(process.hltHIMB*process.selectV0CandidatesNewlambda*process.corr_ana)
process.corr_ana.IsCorr = cms.bool(False)
process.corr_ana.nmin = cms.int32(185)
process.corr_ana.nmax = cms.int32(1000)
#process.corr_ana.V0CandidateCollection = cms.string('selectV0CandidatesNewlambda')
process.corr_ana.V0CandidateCollection = cms.string('generalV0CandidatesNew')
process.corr_ana.TriggerID = cms.string('Lambda')
process.corr_ana.IsBoostRestFrameV0 = cms.bool(True)
process.corr_ana.pttrgmin = cms.vdouble(0.0, 1.0, 2.0, 3.0, 4.0)
process.corr_ana.pttrgmax = cms.vdouble(1.0, 2.0, 3.0, 4.0, 10.0)
