import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v7'
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIHM.HLTPaths = ['HLT_PAFullTracks_Multiplicity185_v*'] # for allphysics
process.hltHIHM.andOr = cms.bool(True)
process.hltHIHM.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/RecoSkim2016_pPb_V0_v1/170817_174330/0000/pPb_HM_11.root'
                ),
                                secondaryFileNames = cms.untracked.vstring(
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/6A492ED2-FF08-E711-BCB1-3417EBE644DA.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/6A753DD4-1209-E711-9D00-A0000220FE80.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/6ACE1DA6-240F-E711-8F7D-FA163E8A53F1.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/7088D290-C00E-E711-910A-FA163EF0BFAF.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/720FF846-CF09-E711-B737-1866DA7F9778.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/728A27E6-610A-E711-8D2C-1CB72C0A3DC1.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/760BB0D8-C10E-E711-804B-FA163E9F00FD.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/76971D5F-270B-E711-B102-1866DA7F9225.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/78053BA6-FF08-E711-BE0C-1866DA7F952E.root',
'/store/himc/pPb816Summer16DR/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/AODSIM/MB_80X_mcRun2_pA_v4-v2/120000/78348924-F008-E711-B38E-002590D0B05E.root'
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
process.corr_ana_cms_Pbp.V0CandidateCollection = cms.InputTag("selectV0CandidatesNewlambda:Lambda")
#process.corr_ana.V0CandidateCollection = cms.InputTag("generalV0CandidatesNew:Lambda")
process.ana = cms.Path(process.selectV0CandidatesNewlambda*process.corr_ana_cms_Pbp)

#process.corr_ana.nmin = cms.int32(185)
#process.corr_ana.nmax = cms.int32(250)

#process.output_HM = cms.OutputModule("PoolOutputModule",
#    outputCommands = cms.untracked.vstring('drop *','keep *_*Candidates*_*_*'),
#    fileName = cms.untracked.string('V0.root'),
#)
#process.output_HM_step = cms.EndPath(process.output_HM)
