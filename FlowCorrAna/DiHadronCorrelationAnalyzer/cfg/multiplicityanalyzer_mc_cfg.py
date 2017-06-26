import FWCore.ParameterSet.Config as cms

process = cms.Process("mult")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v13'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.hltHIUCC = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIUCC.HLTPaths = ['HLT_HIUCC*_*'] # for allphysics
process.hltHIUCC.andOr = cms.bool(True)
process.hltHIUCC.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/ppRECO_std_v3/160216_232421/0000/step2pp_RAW2DIGI_L1Reco_RECO_1.root'
'/store/user/gsfs/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_30_100_w_pp_RECO_20160724/160725_221957/0000/step3_FILTER_RAW2DIGI_L1Reco_RECO_102.root'
                )
                            )

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.multiplicityanalyzer_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('multiplicityanalyzer_mc.root')
                                   )

process.ana = cms.Path(process.mult_ana)
