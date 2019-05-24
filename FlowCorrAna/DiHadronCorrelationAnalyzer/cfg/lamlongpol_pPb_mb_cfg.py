import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(3000)
)

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v7'
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltHIHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHIHM.HLTPaths = ['HLT_PAFullTracks_Multiplicity185_v*'] # for allphysics
#process.hltHIHM.andOr = cms.bool(True)
#process.hltHIHM.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'root://cmsxrootd.fnal.gov//store/user/davidlw/PAMinimumBias1/RecoSkim2016_pPb_V0Cascade_v1/170302_094853/0000/pPb_HM_1.root'
                ),
                                secondaryFileNames = cms.untracked.vstring(
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/479/00000/4E546F7B-DBAE-E611-B49E-FA163E63A392.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/480/00000/126AB4C4-2CAF-E611-93B9-FA163E41A46B.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/480/00000/2CB5DFE9-2BAF-E611-A0A9-FA163EA4BCD2.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/480/00000/52EDED08-28AF-E611-82AC-02163E0124B5.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/480/00000/9CDBDF3A-30AF-E611-8365-02163E01252E.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/480/00000/C8B078A7-24AF-E611-ADF7-FA163EDC366E.root',
'root://cmsxrootd.fnal.gov//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/480/00000/F42B4F03-32AF-E611-9CC6-02163E011CAE.root'
)
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.lamlongpoldata_cff")

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

#process.corr_ana.nmin = cms.int32(185)
#process.corr_ana.nmax = cms.int32(250)

#process.output_HM = cms.OutputModule("PoolOutputModule",
#    outputCommands = cms.untracked.vstring('drop *','keep *_*Candidates*_*_*'),
#    fileName = cms.untracked.string('V0.root'),
#)
#process.output_HM_step = cms.EndPath(process.output_HM)
