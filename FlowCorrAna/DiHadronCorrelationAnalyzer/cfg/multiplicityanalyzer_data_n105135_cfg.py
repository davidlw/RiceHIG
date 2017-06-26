import FWCore.ParameterSet.Config as cms

process = cms.Process("mult")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_dataRun2_PromptHI_v3'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHM.HLTPaths = ['HLT_PixelTracks_Multiplicity85*_v*'] # for allphysics
process.hltHM.andOr = cms.bool(True)
process.hltHM.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/HighMultiplicityEOF/RecoSkim2016_2016H_MD34_HM_v1/161011_171637/0000/pPb_HM_10.root'
                )
                            )

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.multiplicityanalyzer_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('multiplicityanalyzer.root')
                                   )

process.mult_ana.IsGenMult = cms.bool(False)
process.ana = cms.Path(process.hltHM105135PP13TeV*process.mult_ana)
#process.ana = cms.Path(process.mult_ana)
