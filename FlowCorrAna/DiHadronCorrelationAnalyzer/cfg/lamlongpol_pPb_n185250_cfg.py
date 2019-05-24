import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v7'
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_PAFullTracks_Multiplicity185_v*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'root://cmsxrootd.fnal.gov//store/user/davidlw/PAHighMultiplicity1/RecoSkim2016_pPb_V0Cascade_v1/170301_201909/0000/pPb_HM_101.root'
#'root://cmsxrootd.fnal.gov//store/user/davidlw/PAHighMultiplicity1/RecoSkim2016_pPb_V0Cascade_v1/170301_201909/0000/pPb_HM_112.root'
                ),
                                secondaryFileNames = cms.untracked.vstring(
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAHighMultiplicity1/AOD/PromptReco-v1/000/285/517/00000/0499F27C-2DB0-E611-8B1F-02163E014794.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAHighMultiplicity1/AOD/PromptReco-v1/000/285/517/00000/2E66AA87-2DB0-E611-88B3-FA163E8A7AF7.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAHighMultiplicity1/AOD/PromptReco-v1/000/285/517/00000/586A4582-2DB0-E611-8FCA-FA163E0BB21A.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAHighMultiplicity1/AOD/PromptReco-v1/000/285/517/00000/A412D97C-2DB0-E611-B1F3-FA163E3702A7.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAHighMultiplicity1/AOD/PromptReco-v1/000/285/517/00000/BCF96C85-2DB0-E611-A6C2-02163E0143C2.root'
)
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.lamlongpoldata_cfi")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
#    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
#process.hltHIMB.andOr = cms.bool(True)
#process.hltHIMB.throw = cms.bool(False)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('lampol.root')
                                   )

process.load("RiceHIG.V0Analysis.v0selector_cff")
process.selectV0CandidatesNewlambda.v0CollName = cms.InputTag("generalV0CandidatesNew:Lambda")
process.corr_ana.V0CandidateCollection = cms.InputTag("selectV0CandidatesNewlambda:Lambda")
#process.corr_ana.V0CandidateCollection = cms.InputTag("generalV0CandidatesNew:Lambda")
process.ana = cms.Path(process.selectV0CandidatesNewlambda*process.corr_ana)

#process.output_HM = cms.OutputModule("PoolOutputModule",
#    outputCommands = cms.untracked.vstring('drop *','keep *_*Candidates*_*_*'),
#    fileName = cms.untracked.string('V0.root'),
#)
#process.output_HM_step = cms.EndPath(process.output_HM)
